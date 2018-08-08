#pragma once


#ifndef ENTITY
#define ENTITY

//#include "life.h"
#include "LifePlus.h"
#include "EntityController.h"

#include "cocos2d.h"

class EntityController;

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

	~Entity();

	CREATE_FUNC(Entity);
	static Entity* createWith(const char* fileName);

	virtual void update(float dt)override;//

	void hitAir(float time,float height);

	void moveUpdate(Vec2 * velocity,float dt);

	void setController(EntityController* controller);

	EntityController* getController()const;


private:
	CC_SYNTHESIZE_READONLY(int,_collideGroup,CollideGroup);
	void setCollideGroup(int group);

	CC_SYNTHESIZE(Entity3DInfo,_entity3dInfo,Entity3DInfo);

	CC_SYNTHESIZE(Vec2,_entityVelocity,EntityVelocity);

	CC_SYNTHESIZE(Vec2,_controlledVelocity,ControlledVelocity);

	CC_SYNTHESIZE_READONLY(EntityState,_entityState,EntityState);//EntityState _entityState;
	void setEntityState(EntityState state);
	
	CC_SYNTHESIZE(float,_healthPoint,HealthPoint);//float _healthPoint;

	CC_SYNTHESIZE(float,_powerPoint,PowerPoint);//float _powerPoint;

	CC_SYNTHESIZE(int,_teamFlag,TeamFlag);//int _teamFalg;

	CC_SYNTHESIZE(Sprite3D*,_sprite3D,Sprite3D);//Sprite3D * _sprite3D;

	CC_SYNTHESIZE_READONLY(LifePlus*,_lifeBar,LifeBar);//LifePlus* _lifeBar;
	void setLifeBar(LifePlus* lifeBar);

	//CC_SYNTHESIZE_RETAIN(EntityController*,_controller,Controller);//!!bug sometime nullptr
	//controller 
	EntityController* _controller;

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

	EventDispatcher* _dispatcher = Director::getInstance()->getEventDispatcher();

	bool onContactBegin(PhysicsContact& contact);

	bool onContactPreSolve(PhysicsContact& contact,PhysicsContactPreSolve& solve);

	void onContactSeparate(PhysicsContact& contact);

	EventListenerPhysicsContactWithGroup* createWallListener(int group);
};
#endif // !ENTITY