#pragma once


#ifndef SKILL_PLAINATTACK
#define SKILL_PLAINATTACK

#include "cocos2d.h"
#include "Skill.h"
#include"PhysicsShapeCache.h"

USING_NS_CC;

#define ROCKETSPEED 300.0f

#define ATTACKRANGE 1000.0f

class Skill_PlainAttack :public Skill
{
public:
	Skill_PlainAttack();

	CREATE_FUNC(Skill_PlainAttack);

	CC_SYNTHESIZE(SkillRocker*,_skillRocker,SkillRocker);

protected:
	virtual bool init()override;

	TextureCache* _textureCache = Director::getInstance()->getTextureCache();

	PhysicsShapeCache* _physicsCache = PhysicsShapeCache::getInstance();

	void skillTriggerCalledBack(SkillInfo*);

	void destroy(Sprite* sprite);

	EventListenerPhysicsContactWithGroup * createListener(Sprite* sprite);

	EventDispatcher* _dispatcher = Director::getInstance()->getEventDispatcher();
	//void hitCallBack();
};

#endif // !SKILL_PLAINATTACK
