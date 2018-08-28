#include "Entity.h"
#include "EntityController.h"

Entity::Entity() {
	_controller = nullptr;
}

Entity::~Entity()
{
	//CC_SAFE_RELEASE(_controller);
}

Entity * Entity::createWith(const char * fileName)
{
	auto rootNode = Entity::create();

	if (!rootNode->inintWith(fileName))
	{
		return nullptr;
	}


	return rootNode;
}

void Entity::update(float dt)
{
	//CCLOG("Entity::update()");

	_step = 1;

	if (_entityState==normal)//normal state, move at will
	{
		moveUpdate(&_entityVelocity,dt);
	}
	else//controlled by other controllers or buffs
	{
		moveUpdate(&_controlledVelocity,dt);
	}
}

void Entity::hitAir(float time, float height)
{
	auto action = JumpBy::create(time,Vec2(0,0),height,1);

	_sprite3D->runAction(action);
}

void Entity::moveUpdate(Vec2 * velocity,float dt)
{
	//CCLOG("_contacts.size() %i",_contacts.size());
	

	_realVolecity = *velocity;
	/*if (_contacts.size() >= 2)
	{
		CCLOG("stop");
	}*/
	int realContact = 0;
	for (auto item : _contacts)
	{
		auto data = item->getContactData();

		if (collideJudgeByNormal(item))
		{
			realContact++;
			if (realContact >= 2)
			{
				_realVolecity = Point::ZERO;
				break;
			}
			//auto normal = item->getContactData()->normal/item->getContactData()->normal.length();
			auto normal = item->getContactData()->normal;
			if (item->getShapeB()->getBody()->getOwner() == this)
			{
				normal *= -1;
			}

			//CCLOG("nornal: %.3f %.3f",data->normal.x,data->normal.y);

			float product = (_realVolecity.x * normal.x + _realVolecity.y * normal.y);

			_realVolecity = _realVolecity - product*normal;//why divided by 2 to balance?????
		}
	}

	//debug
	/*if (_realVolecity.length()!=0)
	{
		CCLOG("_realVolecity: %.3f %.3f  _contacts:%i  positon:%f,%f", _realVolecity.x, _realVolecity.y, _contacts.size(), getPosition().x,getPosition().y);
	}*/
	
	this->setPosition(this->getPosition() + _realVolecity*dt);

	if (velocity->length()!=0)
	{
		this->getSprite3D()->setRotation(-CC_RADIANS_TO_DEGREES(velocity->getAngle()) + 90);

		//this->getLifeBar()->setRotation(-this->getRotation());
	}
	

}

void Entity::setController(EntityController * controller)
{
	if (controller!=_controller)
	{
		this->removeChild(_controller);

		_controller = controller;

		this->addChild(_controller);
	}

	
}

EntityController * Entity::getController() const
{
	return _controller;
}

void Entity::setCollideGroup(int group)
{
	_collideGroup = group;

	_dispatcher->removeEventListener(_newListener);

	_newListener = createWallListener();

	_dispatcher->addEventListenerWithSceneGraphPriority(_newListener, this);

}

bool Entity::inintWith(const char * fileName)
{
	if (!Node::init())
	{
		return false;
	}

	_sprite3D = Sprite3D::create(fileName);

	_sprite3D->setRotation3D(Vec3(0,0,0));

	_sprite3D->setPosition(Point::ZERO);

	_sprite3D->setPositionZ(0.0f);

	auto aabb = _sprite3D->getAABB();

	_entity3dInfo.a = aabb._max.x - aabb._min.x;
	_entity3dInfo.b = aabb._max.y - aabb._min.y;
	_entity3dInfo.c = aabb._max.z - aabb._min.z;

	this->addChild(_sprite3D);

	_lifeBar = LifePlus::creatWithMaxLife(100,"Life/LifePlus.csb");

	//_lifeBar->setPosition(Point::ZERO);
	_lifeBar->setPosition(Vec2(0,_entity3dInfo.c+50));

	_lifeBar->setGlobalZOrder(200);

	_lifeBar->setScaleX(1.3*(_entity3dInfo.a + _entity3dInfo.b) /LIFEBARWIDTH);
	_lifeBar->setScaleY(0.8f);

	this->addChild(_lifeBar,10);

	_teamFlag = 0;

	_entityVelocity = Point::ZERO;

	_entityState = normal;

	return true;
}

void Entity::onEnter()
{
	Node::onEnter();

	scheduleUpdate();

	_newListener = createWallListener();

	//_dispatcher->addEventListenerWithFixedPriority(_newListener, 1);
	_dispatcher->addEventListenerWithSceneGraphPriority(_newListener, this);
}

void Entity::onExit()
{
	Director::getInstance()->getEventDispatcher()->removeEventListener(_newListener);
	Node::onExit();
}

bool Entity::collideJudgeByNormal(PhysicsContact * contact)
{
	bool tempAB = contact->getShapeB()->getBody()->getOwner() == this;

	auto data = contact->getContactData();

	Vec2 normal = data->normal / data->normal.length();

	float product = (_entityVelocity.x * normal.x + _entityVelocity.y * normal.y);

	return  (tempAB)^(product>0);

}

bool Entity::onContactBegin(PhysicsContact & contact)
{
	//CCLOG("onContactBegin _contacts:%i",_contacts.size());

	for (auto item:_contacts)
	{
		if (item==&contact)
		{
			return false;
		}
	}

	if (contact.getShapeA()->getBody()->getOwner() == this )
	{
		Wall* wall = dynamic_cast<Wall*>(contact.getShapeB()->getBody()->getOwner());
		if (wall && wall->getIsWall()==true )
		{
			_contacts.push_back(&contact);

			return true;
		}
		
	}
	else if (contact.getShapeB()->getBody()->getOwner() == this)
	{
		Wall* wall = dynamic_cast<Wall*>(contact.getShapeA()->getBody()->getOwner());
		if (wall && wall->getIsWall() == true)
		{
			_contacts.push_back(&contact);

			return true;
		}
	}
	return false;
}

bool Entity::onContactPreSolve(PhysicsContact & contact, PhysicsContactPreSolve & solve)
{
	return true;
}

void Entity::onContactSeparate(PhysicsContact & contact)
{
	if (_contacts.size() == 0)
	{
		return;
	}
	for (unsigned int i=0;i<=_contacts.size()-1;i++)
	{
		if (_contacts.at(i)==&contact)
		{
			_contacts.erase(_contacts.begin()+i);
			return;
		}
	}

	//CCLOG("onContactSeperate_contacts:%i", _contacts.size());
	
}

EventListenerPhysicsContact * Entity::createWallListener()
{
	auto newListener = EventListenerPhysicsContact::create();

	newListener->onContactBegin = CC_CALLBACK_1(Entity::onContactBegin, this);

	newListener->onContactPreSolve = CC_CALLBACK_2(Entity::onContactPreSolve, this);

	newListener->onContactSeparate = CC_CALLBACK_1(Entity::onContactSeparate, this);

	return newListener;
}

void Entity::entityDie()
{
	if (onEntityDie)
	{
		onEntityDie(this);
	}

	_event=EventCustom("EntityDie");

	_event.setUserData(this);

	_dispatcher->dispatchEvent(&_event);

}

void Entity::setEntityState(EntityState state)
{
	_entityState = state;
}

void Entity::setLifeBar(LifePlus * lifeBar)
{
	_lifeBar = lifeBar;
}
