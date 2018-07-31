#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "3d/CCSPrite3D.h"
#include "PhysicsShapeCache.h"

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

	void keyboardCallBack(EventKeyboard::KeyCode keyCode,Event * event);

	PhysicsShapeCache* _cache;
	
};

#endif // __HELLOWORLD_SCENE_H__
