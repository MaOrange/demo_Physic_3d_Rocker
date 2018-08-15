#pragma once


#ifndef SKILL
#define SKILL

#include "cocos2d.h"
USING_NS_CC;

#include "SkillRocker.h"
#include "GameProtocol.h"

class EntityController;

class Entity;

class Skill:public GameProtocol 
{
public:
	Skill();

	CC_SYNTHESIZE(SkillRocker*,_skillRocker,SkillRocker);

	CREATE_FUNC(Skill);

	CC_SYNTHESIZE(EntityController*,_entityController,EntityController);

protected:
	virtual bool init()override;

	


};

#endif // !SKILL
