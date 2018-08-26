#pragma once

#ifndef SCENEMANAGER
#define SCENEMANAGER

#include"cocos2d.h"
USING_NS_CC;

class HelloWorld;

class SceneManager 
{
public:
	SceneManager();

	static SceneManager* getInstance();
protected:
	static SceneManager* _instance;
};

#endif // !SCENEMANAGER
