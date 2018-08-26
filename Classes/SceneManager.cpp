#include "SceneManager.h"
#include"HelloWorldScene.h"

SceneManager::SceneManager() {
    
}

SceneManager * SceneManager::getInstance()
{
	if (!_instance)
	{
		_instance = new SceneManager;
	}

	return _instance;
}
