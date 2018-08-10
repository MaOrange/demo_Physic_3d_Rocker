#pragma once


#ifndef CRAB
#define CRAB

#include"cocos2d.h"
#include"EntityController.h"

USING_NS_CC;

#define TNRNPACE 2.0f

enum CrabState
{
	underAttack,runningAround,died
};

class EnemyController_Crab:public EntityController
{
public:

	CREATE_FUNC(EntityController);

	EnemyController_Crab();
	~EnemyController_Crab();

	void damage(float value);

	void recover(float value);

	void update(float dt)override;

	CC_SYNTHESIZE(Vec2,_crabVelocity,CrabVelocity);

	

protected:

	bool init()override;

	float _timer = 0;


};

#endif // !CRAB
