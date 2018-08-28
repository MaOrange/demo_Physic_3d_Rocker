#pragma once

#ifndef ENEMYCONTROLLER_ADC
#define ENEMYCONTROLLER_ADC

#include"cocos2d.h"
USING_NS_CC;
#include "EnemyController_STD.h"
#include"SimpleAudioEngine.h"
using namespace CocosDenshion;

#define ADC_ATTACK_PACE 2.0f

#define ADC_SPEED 300.0f

#define ROCKER_SPEED 900.0f

#define SAFE_DISTENCE 670.0f

enum adcState
{
	adcDead, runningAttack,standingAttack
};

class EnemyController_ADC :public EnemyController_STD
{
public:
	EnemyController_ADC();

	CREATE_FUNC(EnemyController_ADC);

	CC_SYNTHESIZE(adcState,_state,State);
protected:
	virtual bool init()override;

	virtual void attack(Vec2 dir)override;

	virtual void update(float dt)override;

	float _attackTimer=0;

	void turnDirection(Vec2 vec);

	void hitCalledBack(Node* node,Entity* entity,PhysicsContactData cData);
};
#endif // !ENEMYCONTROLLER_ADC

