#pragma once



#ifndef ENTITYCONTROLLER
#define ENTITYCONTROLLER

#include"cocos2d.h"
#include"Buff.h"
USING_NS_CC;

class EntityController :public Ref
{
public:
	EntityController();

	~EntityController();

	void addBuff(Buff* buff);
protected:
	CC_SYNTHESIZE(Vector<Buff*>,_buffs,Buffs);


};
#endif // !ENTITYCONTROLLER
