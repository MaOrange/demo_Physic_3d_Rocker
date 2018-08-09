#pragma once


#ifndef HEROCONTROLLER
#define HEROCONTROLLER

#include"cocos2d.h"
//#include"Rocker.h"
#include"SkillRocker.h"//include bug?
#include"EntityController.h"

USING_NS_CC;

class Entity;

enum HeroAnimationTag
{
	move
};

class HeroController:public EntityController 
{
public:
	HeroController();

	~HeroController();

	CREATE_FUNC(HeroController)

	virtual void update(float dt)override;

	virtual void onEnter()override;

	virtual void onExit()override;

	void rockerChange(Vec2 vec);
	
	CC_SYNTHESIZE(Entity*, _entityControlled, EntityControlled);

	CC_SYNTHESIZE(Vec2,_heroVelocity,HeroVelocity);

	CC_SYNTHESIZE_READONLY(Rocker*,_rocker,Rocker);

	CC_SYNTHESIZE_RETAIN(Animation3D*,_animation,Animation);

	CC_SYNTHESIZE_RETAIN(Animate3D*,_animate_Move,Animate_Move);
	
	CC_SYNTHESIZE_RETAIN(RepeatForever*,_animate_Move_Forever,Animation_Move_Forever);
	
	void setRocker(Rocker* rocker);
protected:
	virtual bool init()override;

	//Animation3D * _animation;
	

	//Animate3D * _animate_Move;
	

	//RepeatForever* _animate_Move_Forever;
	

};

#endif // !HEROCONTROLLER

