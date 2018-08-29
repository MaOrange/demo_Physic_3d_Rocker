#pragma once


#ifndef _SKILL_ICYBLAST_H
#define _SKILL_ICYBLAST_H

#include "Skill.h"

#include"cocos2d.h"
#include"PhysicsShapeCache.h"

#include "Combo.h"

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

USING_NS_CC;

#define SENSIBILITY 3.0f

class Skill_IcyBlast:public Skill
{
public:
	Skill_IcyBlast();

	CREATE_FUNC(Skill_IcyBlast);

	virtual void setEntityController(EntityController* controller)override;
protected:
	virtual bool init()override;

	Sprite* _ice;

	Sprite* _skillPos;

	virtual void skillTriggerCalledBack(SkillInfo*)override;

	virtual void skillDirectionCallBack(Vec2 & vec)override;

	unsigned int _camMask;

	PhysicsShapeCache* _pCache=PhysicsShapeCache::getInstance();

	EventDispatcher* _dispatcher = Director::getInstance()->getEventDispatcher();

	void hit(Entity* entity,PhysicsContactData cData);
};

#endif // !_SKILL_ICYBLAST_H
