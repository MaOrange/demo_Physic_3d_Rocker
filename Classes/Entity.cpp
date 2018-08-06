#include "Entity.h"

Entity::Entity() {
    
}

Entity * Entity::createWith(const char * fileName)
{
	auto rootNode = Entity::create();

	if (!rootNode->init())
	{
		return nullptr;
	}


	return rootNode;
}

void Entity::update(float dt)
{
	_step = _entityVelocity.length()*dt+1;

	for (int i=1;i<=_step;i++)
	{
		_realVolecity = _entityVelocity;
		for (auto item:_contacts)
		{
			auto data = item->getContactData();

			if (collideJudgeByNormal(item))
			{
				auto normal = item->getContactData()->normal;

				float product = (_entityVelocity.x * normal.x + _entityVelocity.y * normal.y);

				_realVolecity = _realVolecity - product*normal / pow(normal.length(),2);
			}
		}

		this->setPosition(this->getPosition() + _realVolecity*dt/_step);
		this->setRotation(-CC_RADIANS_TO_DEGREES(_entityVelocity.getAngle()) + 90);
	}
}

void Entity::hitAir(float time, float height)
{
	auto action = JumpBy::create(time,Vec2(0,0),height,1);

	_sprite3D->runAction(action);
}

bool Entity::inintWith(const char * fileName)
{
	if (!Node::init())
	{
		return false;
	}

	_sprite3D = Sprite3D::create(fileName);

	auto aabb = _sprite3D->getAABB();

	_entity3dInfo.a = aabb._max.x - aabb._min.x;
	_entity3dInfo.b = aabb._max.y - aabb._min.y;
	_entity3dInfo.c = aabb._max.z - aabb._min.z;

	this->addChild(_sprite3D);

	_lifeBar = LifePlus::creatWithMaxLife(100,"");

	_lifeBar->setPosition(Vec2(0,_entity3dInfo.c+10));

	this->addChild(_lifeBar);

	_teamFlag = 0;

	_entityVelocity = Point::ZERO;

	return true;
}

void Entity::onEnter()
{
	_newListener = EventListenerPhysicsContactWithGroup::create(_collideGroup);

	_newListener->onContactBegin = [=](PhysicsContact& contact)->bool
	{
		if (contact.getShapeA()->getBody()->getOwner()==this || contact.getShapeB()->getBody()->getOwner() == this)
		{
			_contacts.pushBack(&contact);

			return true;
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
