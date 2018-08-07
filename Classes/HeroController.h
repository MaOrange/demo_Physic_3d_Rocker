#pragma once


#ifndef HEROCONTROLLER
#define HEROCONTROLLER

#include"cocos2d.h"
//#include"Rocker.h"
#include"SkillRocker.h"//include bug?
#include"EntityController.h"

USING_NS_CC;

class Entity;

class HeroController:public EntityController 
{
public:
	HeroController();

	CREATE_FUNC(HeroController)

	virtual void update(float dt)override;

	virtual void onEnter()override;

	virtual void onExit()override;

protected:
	virtual bool init()override;

	CC_SYNTHESIZE(Entity*, _entityControlled, EntityControlled);

	CC_SYNTHESIZE(Vec2,_heroVelocity,HeroVelocity);

	CC_SYNTHESIZE_READONLY(Rocker*,_rocker,Rocker);

	void setRocker(Rocker* rocker);
};

#endif // !HEROCONTROLLER

