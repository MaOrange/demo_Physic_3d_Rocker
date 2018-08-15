#pragma once


#ifndef ENEMYCONTROLLER_STD
#define ENEMYCONTROLLER_STD

#define ENEMY_FILE "3D/EnemyAnimation.c3b"

#define _ATTACKEFFECT "Skill/EnemyAttack_close.png"

#define _ATTACKEFFECT_PHYSICS "Skill/EnemyAttack.plist"

#define MOVE_ANIMATE_BEGIN 0.0f/60.0f

#define MOVE_ANIMATE_END 80.0f/60.0f

#define ATTACK_ANIMATE_BEGIN 100.0f/60.0f

#define ATTACK_ANIMATE_END 150.0f/60.0f

#define DIE_ANIMATE_BEGIN 160.f/60.0f

#define DIE_ANIMATE_END 180.0f/60.0f

#define HUNT_PACE 2.0f

#define SPEED 500.0f

#define STD_DAMAGE 7.0f

#define RANGE 200.0f

#include"cocos2d.h"
USING_NS_CC;

#include"EntityController.h"
#include "PhysicsShapeCache.h"

enum Enemy_STD_state
{
	hunting,attacking,dead
};

class EnemyController_STD :public EntityController
{
public:
	EnemyController_STD();
	~EnemyController_STD();

	static void preLoad();

	CREATE_FUNC(EnemyController_STD);

	CC_SYNTHESIZE(Enemy_STD_state,_enemyState,enemyState);

	CC_SYNTHESIZE_RETAIN(Animation3D*,_animation,Animation);

	CC_SYNTHESIZE_RETAIN(RepeatForever*,_animate_move,Animate_move);

	CC_SYNTHESIZE_RETAIN(Animate3D*,_animate_attack,Animate_attack);

	CC_SYNTHESIZE_RETAIN(Animate3D*, _animate_die,Animate_die);

	CC_SYNTHESIZE_RETAIN(Sequence*,_attackEffect,AttackEffect);

	CC_SYNTHESIZE(Entity*,_attackTarget,AttackTarget);

	virtual void update(float dt)override;

	virtual void setEntityControlled(Entity* entity)override;

	//virtual void onEnter()override;

protected:
	virtual bool init()override;

	TextureCache* _textureCache = Director::getInstance()->getTextureCache();

	PhysicsShapeCache* _physicsCache=PhysicsShapeCache::getInstance();

	float _huntTimer = 0;

	bool isInRange();

	Vec2 findDelta();

	void attack(Vec2 dir);
	
	Vec2 _enemyVelocity;

	float _attackTimer=0;

	float _attackDelayTimer = 0;

	EventListenerPhysicsContact * createListener(Sprite* sprite);

	EventDispatcher* _dispatcher = Director::getInstance()->getEventDispatcher();

	static bool _isLoad;
};
#endif // !ENEMYCONTROLLER_STD

