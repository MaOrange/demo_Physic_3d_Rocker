#pragma once

#ifndef GAMEPROTOCOL
#define GAMEPROTOCOL

#include "Entity.h"

USING_NS_CC;

class GameProtocol :public Node
{
public:
	GameProtocol();

	~GameProtocol();

	std::vector<int> _targets;
protected:
	virtual bool init()override;

	EventListenerPhysicsContact* createHitListener(Sprite * sprite);

	std::function<void(Entity* target)> hitCallBack = nullptr;

	Vector<PhysicsContact*> _contacts;

	void delayCall(const std::function<void()>& callback, float delay);


};
#endif // !GAMEPROTOCOL

