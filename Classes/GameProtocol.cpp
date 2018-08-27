#include "GameProtocol.h"

GameProtocol::GameProtocol() {
    
}

GameProtocol::~GameProtocol()
{
	_targets.clear();
}


bool GameProtocol::init()
{
	if (!Node::init())
	{
		return false;
	}

	return true;
}

EventListenerPhysicsContact * GameProtocol::createHitListener(Node * node)
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


		if (contact.getShapeA()->getBody()->getOwner() == node)
		{
			Entity* entity = (dynamic_cast<Entity*>(contact.getShapeB()->getBody()->getOwner()));
			for (auto item : _targets)
			{
				if (entity && entity->getTeamFlag() == item)
				{
					if (hitCallBack)
					{
						hitCallBack(node,entity, *contact.getContactData());
					}
					_contacts.push_back(&contact);
					return true;
				}
			}
		}

		else if (contact.getShapeB()->getBody()->getOwner() == node)
		{
			Entity* entity = (dynamic_cast<Entity*>(contact.getShapeA()->getBody()->getOwner()));
			for (auto item : _targets)
			{
				if (entity && entity->getTeamFlag() == item)
				{
					if (hitCallBack)
					{
						hitCallBack(node,entity, *contact.getContactData());
					}
					_contacts.push_back(&contact);
					return true;
				}
			}
		}
		return false;
	};

	newListener->onContactSeparate = [=](PhysicsContact & contact)->void
	{
		if (_contacts.size() == 0)
		{
			return;
		}
		for (unsigned int i = 0; i <= _contacts.size() - 1; i++)
		{
			if (_contacts.at(i) == &contact)
			{
				_contacts.erase(_contacts.begin() + i);
				return;
			}
		}
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

bool GameProtocol::playEffect(const char* fileName)
{
	if (!audioIsCD)
	{
		SimpleAudioEngine::getInstance()->playEffect(fileName);

		audioIsCD = true;

		delayCall([=]() {audioIsCD = false; },0.3);

		return true;
	}

	return false;
}
