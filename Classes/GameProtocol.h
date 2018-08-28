#pragma once

#ifndef GAMEPROTOCOL
#define GAMEPROTOCOL

#include "Entity.h"

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

USING_NS_CC;

class GameProtocol :public Node
{
public:
	GameProtocol();

	~GameProtocol();

	std::vector<int> _targets;
protected:
	virtual bool init()override;

	EventListenerPhysicsContact* createHitListener(Node * node);

	std::function<void(Node* caller,Entity* target,PhysicsContactData cData)> hitCallBack = nullptr;

	std::vector<PhysicsContact*> _contacts;

	void delayCall(const std::function<void()>& callback, float delay);

	bool audioIsCD=false;

	bool playEffect(const char* fileName);
};
#endif // !GAMEPROTOCOL

