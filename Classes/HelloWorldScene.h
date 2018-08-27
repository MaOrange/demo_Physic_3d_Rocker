#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "3d/CCSPrite3D.h"
#include "PhysicsShapeCache.h"
#include "SkillRocker.h"
#include "Entity.h"
#include "HeroController.h"
#include "Wall.h"
#include "EnemyController_STD.h"
#include "Skill_IcyBlast.h"
#include "Skill_IcyBlock.h"
#include "Skill_Flash.h"
#include "ScoreBoard.h"
#include"EnemyController_ADC.h"
#include "SceneManager.h"
#include"Config.h"

USING_NS_CC;

class HelloWorld : public cocos2d::Layer
{
public:
	enum ButtionFlag
	{
		left,
		right,
		up,
		down,
		front,
		back
	
	};

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(HelloWorld);

	Size size = Director::getInstance()->getVisibleSize();

	Sprite3D * sprite3d;

	Camera* _camera_hero;

	Camera* _camera_bg;

	Sprite3D* _hero;

	Node* _box;

	PhysicsContact * _contect;

	void keyboardCallBack(EventKeyboard::KeyCode keyCode,Event * event);

	PhysicsShapeCache* _cache;
	
	Rocker* _rocker;

	Scene* _scene;

	Vec2 v;

	Entity* _heroEntity;

	EntityController * _heroController;

	Vector<PhysicsContact*> _contacts;

	virtual void onEnter()override;

	virtual void onExit()override;

	virtual void update(float dt);

	EventListenerCustom* _dieListener;

	void addEnemySTD();

	EventDispatcher* _dispatcher = Director::getInstance()->getEventDispatcher();

	std::string ranKey();

	void delayCall(const std::function<void()>& callback,float delay);

	void cameraUpdate();

	ScoreBoard* _score;

	ParticleSystem* _soulFire;

	void enemyDie(Entity* enemy);

	Vec2 convertToPosInCamera(const Vec2& vec);

	short int _colorState=1;

	void changeColor();
	float _colorRate=30;

	Layer* _field;

	Layer* _uiLayer;

	Layer* _bg;

	unsigned int randomIntByMax(int max);
};

#endif // __HELLOWORLD_SCENE_H__
