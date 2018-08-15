#include "GameProtocol.h"

GameProtocol::GameProtocol() {
    
}


bool GameProtocol::init()
{
	if (!Node::init())
	{
		return false;
	}

	return true;
}

EventListenerPhysicsContact * GameProtocol::createHitListener(Sprite * sprite)
{
	auto newListener = EventListenerPhysicsContact::create();

	newListener->onContactBegin = [=](PhysicsContact & contact)->bool
	{
		for (auto item : _contacts)
		{
			if (item == &contact)
			{
				return false;
			}
		}//no contact is duplicated


		if (contact.getShapeA()->getBody()->getOwner() == sprite)
		{
			Entity* entity = (dynamic_cast<Entity*>(contact.getShapeB()->getBody()->getOwner()));
			for (auto item : _targets)
			{
				if (entity && entity->getTeamFlag() == item)
				{
					if (hitCallBack)
					{
						hitCallBack(entity);
					}
					_contacts.pushBack(&contact);
					return true;
				}
			}
		}

		else if (contact.getShapeB()->getBody()->getOwner() == sprite)
		{
			Entity* entity = (dynamic_cast<Entity*>(contact.getShapeA()->getBody()->getOwner()));
			for (auto item : _targets)
			{
				if (entity && entity->getTeamFlag() == item)
				{
					if (hitCallBack)
					{
						hitCallBack(entity);
					}
					_contacts.pushBack(&contact);
					return true;
				}
			}
		}
		return false;
	};

	newListener->onContactSeparate = [=](PhysicsContact & contact)->void
	{
		_contacts.eraseObject(&contact);
	};

	return newListener;
}

void GameProtocol::delayCall(const std::function<void()>& callback, float delay)
{
	auto call = CallFunc::create(callback);

	auto Timedelay = DelayTime::create(delay);

	auto combo = Sequence::create(Timedelay, call, NULL);

	this->runAction(combo);
}