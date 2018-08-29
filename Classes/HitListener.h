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

	CC_SYNTHESIZE(int,_comboCount,ComboCount);

	std::function<void(Node* caller, Entity* target, PhysicsContactData cData)> hitCallBack = nullptr;

	void comboPlus();
protected:
	


};
#endif // !COMBOLISTENER

