#pragma once


#ifndef ENTITYCONTROLLER
#define ENTITYCONTROLLER

#include"cocos2d.h"
#include"Buff.h"
USING_NS_CC;

class Enity;

class EntityController :public Node
{
public:
	EntityController();

	~EntityController();

	void addBuff(Buff* buff);

	virtual void onEnter()override;

protected:

	CC_SYNTHESIZE(Vector<Buff*>,_buffs,Buffs);


};
#endif // !ENTITYCONTROLLER
