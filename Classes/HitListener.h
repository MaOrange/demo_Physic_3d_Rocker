#pragma once

#ifndef COMBOLISTENER
#define COMBOLISTENER

#include "cocos2d.h"
USING_NS_CC;
#include"Entity.h"

class HitListener:public EventListenerPhysicsContact
{
public:
	CREATE_FUNC(HitListener);

	HitListener();

	std::function<void(Node* caller, Entity* target, PhysicsContactData cData)> hitCallBack = nullptr;
protected:
	


};
#endif // !COMBOLISTENER

