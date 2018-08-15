#pragma once


#ifndef SKILL
#define SKILL

#include "cocos2d.h"
USING_NS_CC;

#include "SkillRocker.h"

class EntityController;

class Entity;

class Skill:public Node 
{
public:
	Skill();

	CC_SYNTHESIZE(SkillRocker*,_skillRocker,SkillRocker);

	CREATE_FUNC(Skill);

	CC_SYNTHESIZE(EntityController*,_entityController,EntityController);

	std::vector<int> _targets;
protected:
	virtual bool init()override;

	EventListenerPhysicsContact* createHitListener(Sprite * sprite);

	std::function<void(Entity* target)> hitCallBack = nullptr;

	Vector<PhysicsContact*> _contacts;


};

#endif // !SKILL
