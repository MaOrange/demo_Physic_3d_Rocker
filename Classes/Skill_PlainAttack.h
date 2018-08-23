#pragma once


#ifndef SKILL_PLAINATTACK
#define SKILL_PLAINATTACK

#include "cocos2d.h"
#include "Skill.h"
#include"PhysicsShapeCache.h"

USING_NS_CC;

#define ROCKETSPEED 800.0f

#define ATTACKRANGE 800.0f

#define DAMAGE 10.0f

class Skill_PlainAttack :public Skill
{
public:
	Skill_PlainAttack();

	CREATE_FUNC(Skill_PlainAttack);

	CC_SYNTHESIZE(SkillRocker*,_skillRocker,SkillRocker);

	CC_SYNTHESIZE(Sprite*,_skillDirection,SkillDirection);

	virtual void setEntityController(EntityController* controller)override;

protected:
	virtual bool init()override;

	TextureCache* _textureCache = Director::getInstance()->getTextureCache();

	PhysicsShapeCache* _physicsCache = PhysicsShapeCache::getInstance();

	virtual void skillTriggerCalledBack(SkillInfo*)override;

	void destroy(Sprite* sprite);

	EventListenerPhysicsContact * createListener(Sprite* sprite);

	EventDispatcher* _dispatcher = Director::getInstance()->getEventDispatcher();
	//void hitCallBack();

	virtual void skillDirectionCallBack(Vec2 & vec)override;

	void hitEffect(Vec2 pos, Entity* entity);
};

#endif // !SKILL_PLAINATTACK