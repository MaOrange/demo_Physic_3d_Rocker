#include "SceneManager.h"
#include"HelloWorldScene.h"
#include"TitleScene.h"

SceneManager::SceneManager() {
    
}

SceneManager* SceneManager::_instance = new SceneManager;

SceneManager * SceneManager::getInstance()
{
	if (!_instance)
	{
		_instance = new SceneManager;
	}

	return _instance;
}

void SceneManager::toHelloWorld()
{
	auto scene = HelloWorld::createScene();

	_director->replaceScene(scene);
}

void SceneManager::toTitleScene()
{
	auto scene = TitleScene::createScene();

	_director->replaceScene(scene);
}