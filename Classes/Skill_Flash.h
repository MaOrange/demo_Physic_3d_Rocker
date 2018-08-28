#pragma once

#ifndef SKILL_FLASH
#define SKILL_FLASH

#include"cocos2d.h"
#include"Skill.h"

#define FLASH_DIS 300.0f

class Skill_Flash :public Skill
{
public:
	Skill_Flash();

	CREATE_FUNC(Skill_Flash);

	virtual void setEntityController(EntityController* entity)override;
protected:
	virtual bool init()override;

	Sprite* _skillDir;

	virtual void skillTriggerCalledBack(SkillInfo* info);

	virtual void skillDirectionCallBack(Vec2 & vec);

};

#endif // !SKILL_FLASH
