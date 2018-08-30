#pragma once

#ifndef MAINGAME
#define MAINGAME

#include"HelloWorldScene.h"

class MainGame :public HelloWorld 
{
public:
	MainGame();

	static cocos2d::Scene* createScene();

	CREATE_FUNC(MainGame);

	CC_SYNTHESIZE(int,_enemyCount,EnemyCount);
protected:
	virtual bool init()override;

	virtual void heroDie(Entity * entity)override;

	void randomAddEnemyPosLimited(float dt);
};
#endif // !MAINGAME

