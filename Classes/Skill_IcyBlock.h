#pragma once

#ifndef SKILL_ICYBLOCK
#define SKILL_ICYBLOCK

#include"cocos2d.h"
#include"Skill.h"
#include "Config.h"

USING_NS_CC;

#define ICYBLOCK_SENSIBILITY 3.0f

class Skill_IcyBlock:public Skill 
{
public:
	Skill_IcyBlock();

	CREATE_FUNC(Skill_IcyBlock);

	virtual void setEntityController(EntityController* controller)override;
protected:
	virtual void skillDirectionCallBack(Vec2 & vec)override;

	virtual void skillTriggerCalledBack(SkillInfo*)override;

	virtual bool init()override;

	Sprite3D* _skillPos;

};
#endif // !SKILL_ICYBLOCK

