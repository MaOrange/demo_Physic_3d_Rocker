#pragma once


#ifndef CRAB
#define CRAB

#include"cocos2d.h"
#include"EntityController.h"

USING_NS_CC;

#define TURNPACE 2.0f

#define RECOVERPACE 1.5f

#define RECOVER 10.0f

#define MAXHEATH 50.0f

#define VELOCITY 300.0f

enum CrabState
{
	underAttack,runningAround,died
};

class EnemyController_Crab:public EntityController
{
public:

	CREATE_FUNC(EnemyController_Crab);

	EnemyController_Crab();
	~EnemyController_Crab();

	virtual void update(float dt)override;

	CC_SYNTHESIZE(Vec2,_crabVelocity,CrabVelocity);

	CC_SYNTHESIZE(CrabState,_crabState,CrabState);

	virtual void onEnter()override;

	virtual void setEntityControlled(Entity* entity)override;

protected:


	bool init()override;

	float _turnTimer = 0;

	float _recoverTimer = 0;
};

#endif // !CRAB
