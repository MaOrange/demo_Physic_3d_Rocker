#include "Entity.h"
#include "EntityController.h"

Entity::Entity() {
    
}

Entity::~Entity()
{
	CC_SAFE_RELEASE(_controller);
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

	_step = _entityVelocity.length()*dt+1;

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
	for (int i = 1; i <= _step; i++)
	{
		_realVolecity = *velocity;
		for (auto item : _contacts)
		{
			auto data = item->getContactData();

			if (collideJudgeByNormal(item))
			{
				auto normal = item->getContactData()->normal;

				float product = (_entityVelocity.x * normal.x + _entityVelocity.y * normal.y);

				_realVolecity = _realVolecity - product*normal / pow(normal.length(), 2);
			}
		}

		//debug
		if (_realVolecity.length()!=0)
		{
			CCLOG("!");
		}
		
		this->setPosition(this->getPosition() + _realVolecity*dt / _step);

		this->setRotation(-CC_RADIANS_TO_DEGREES(_entityVelocity.getAngle()) + 90);
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

bool Entity::inintWith(const char * fileName)
{
	if (!Node::init())
	{
		return false;
	}

	_sprite3D = Sprite3D::create(fileName);

	_sprite3D->setRotation3D(Vec3(0,0,0));

	_sprite3D->setPosition(Point::ZERO);

	auto aabb = _sprite3D->getAABB();

	_entity3dInfo.a = aabb._max.x - aabb._min.x;
	_entity3dInfo.b = aabb._max.y - aabb._min.y;
	_entity3dInfo.c = aabb._max.z - aabb._min.z;

	this->addChild(_sprite3D);

	_lifeBar = LifePlus::creatWithMaxLife(100,"Life/LifePlus.csb");

	_lifeBar->setPosition(Vec2(0,_entity3dInfo.c+10));

	this->addChild(_lifeBar);

	_teamFlag = 0;

	_entityVelocity = Point::ZERO;

	_entityState = normal;

	return true;
}

void Entity::onEnter()
{
	Node::onEnter();

	scheduleUpdate();

	_newListener = EventListenerPhysicsContactWithGroup::create(_collideGroup);

	_newListener->onContactBegin = [=](PhysicsContact& contact)->bool
	{
		if (contact.getShapeA()->getBody()->getOwner()==this || contact.getShapeB()->getBody()->getOwner() == this)
		{
			_contacts.pushBack(&contact);

			return true;
		}
		else
		{
			return false;
		}
	};

	_newListener->onContactPreSolve = [=](PhysicsContact& contact, PhysicsContactPreSolve& solve)->bool
	{
		return true;//////save cpu overhead or prepare for cases????
	};

	_newListener->onContactSeparate = [=](PhysicsContact& contact)
	{
		_contacts.eraseObject(&contact);
	};

	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_newListener, 1);
}

void Entity::onExit()
{
	Director::getInstance()->getEventDispatcher()->removeEventListener(_newListener);
}

bool Entity::collideJudgeByNormal(PhysicsContact * contact)
{
	bool tempAB = contact->getShapeB()->getBody()->getOwner() == this;

	auto data = contact->getContactData();

	Vec2 normal = data->normal / data->normal.length();

	float product = (_entityVelocity.x * normal.x + _entityVelocity.y * normal.y);

	return (!tempAB)&&(product>0);

}

void Entity::setEntityState(EntityState state)
{
	_entityState = state;
}

void Entity::setLifeBar(LifePlus * lifeBar)
{
	_lifeBar = lifeBar;
}
