#pragma once


#ifndef ENEMYCONTROLLER_STD
#define ENEMYCONTROLLER_STD

#define ENEMY_FILE "3D/EnemyAnimation.c3b"

#define _ATTACKEFFECT "Skill/EnemyAttack_close.png"

#define MOVE_ANIMATE_BEGIN 0.0f/60.0f

#define MOVE_ANIMATE_END 80.0f/60.0f

#define ATTACK_ANIMATE_BEGIN 100.0f/60.0f

#define ATTACK_ANIMATE_END 150.0f/60.0f

#include"cocos2d.h"
USING_NS_CC;

#include"EntityController.h"

class EnemyController_STD :public EntityController
{
public:
	EnemyController_STD();
};
#endif // !ENEMYCONTROLLER_STD

