#pragma once


#ifndef ENTITY
#define ENTITY

#include "life.h"
#include "LifePlus.h"

#include "cocos2d.h"

USING_NS_CC;

enum EntityState
{
	normal, controlled, executing
};

struct Entity3DInfo
{
	float a, b, c;
};

class Entity :public Node
{
public:
	Entity();
	CREATE_FUNC(Entity);
	static Entity* createWith(const char* fileName);

	virtual void update(float dt)override;//

	void hitAir(float time,float height);

	void moveUpdate(Vec2 * velocity,float dt);
private:
	CC_SYNTHESIZE(int,_collideGroup,CollideGroup);

	CC_SYNTHESIZE(Entity3DInfo,_entity3dInfo,Entity3DInfo);

	CC_SYNTHESIZE(Vec2,_entityVelocity,EntityVelocity);

	CC_PROPERTY_READONLY(EntityState,_entityState,State);//EntityState _entityState;
	
	CC_SYNTHESIZE(float,_healthPoint,HealthPoint);//float _healthPoint;

	CC_SYNTHESIZE(float,_powerPoint,PowerPoint);//float _powerPoint;

	CC_SYNTHESIZE(int,_teamFlag,TeamFlag);//int _teamFalg;

	CC_SYNTHESIZE(Sprite3D*,_sprite3D,Sprite3D);//Sprite3D * _sprite3D;

	CC_PROPERTY_READONLY(LifePlus*,_lifeBar,LifeBar);//LifePlus* _lifeBar;

	//CC_SYNTHESIZE(,,);
	//controllor 

	//virtual bool init();

	Vector<PhysicsContact*> _contacts;

	Vec2 _realVolecity;

	virtual bool inintWith(const char* fileName);

	virtual void onEnter();//register physics listener

	virtual void onExit();

	//helper
	bool collideJudgeByNormal(PhysicsContact* contact);

	CC_SYNTHESIZE(int,_step,Step);//int _step;//to avoid tunel effect

	EventListenerPhysicsContactWithGroup* _newListener;
};
#endif // !ENTITY
