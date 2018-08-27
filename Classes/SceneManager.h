#pragma once

#ifndef SCENEMANAGER
#define SCENEMANAGER

#include"cocos2d.h"
USING_NS_CC;

class HelloWorld;
class TitleScene;

class SceneManager 
{
public:
	SceneManager();

	static SceneManager* getInstance();

	void toHelloWorld();

	void toTitleScene();
protected:
	static SceneManager* _instance;

	Director* _director = Director::getInstance();
};

#endif // !SCENEMANAGER