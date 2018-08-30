#include "MainGame.h"

MainGame::MainGame() {
	_enemyCount = 0;
}

cocos2d::Scene * MainGame::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();

	//scene->getPhysicsWorld()->setGravity(Point::ZERO);
	scene->getPhysicsWorld()->setGravity(Vec2(0, 0));

	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	//tunnel bug fix
	scene->getPhysicsWorld()->setAutoStep(true);

	// 'layer' is an autorelease object
	auto layer = MainGame::create();

	layer->_scene = scene;

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool MainGame::init()
{
	if (!HelloWorld::init())
	{
		return false;
	}

	_icyBlast->setCD(3.0f);

	_flash->setCD(2.0f);

	_score->setScore(0);

	schedule(schedule_selector(MainGame::randomAddEnemyPosLimited), 8.0f);

	return true;
}

void MainGame::heroDie(Entity * entity)
{
	_rocker->setEnabled(false);

	_icyBlast->getSkillRocker()->setIsEnable(false);

	_icyBlock->getSkillRocker()->setIsEnable(false);

	_flash->getSkillRocker()->setIsEnable(false);

	_plainAttack->getSkillRocker()->setIsEnable(false);

	delayCall(CC_CALLBACK_0(MainGame::gameOver,this, _score->getScore()),2.0f);
}

void MainGame::randomAddEnemyPosLimited(float dt)
{
	if (_enemyCount>=10)
	{
		unschedule(schedule_selector(MainGame::randomAddEnemyPosLimited));
	}
	else
	{
		_enemyCount++;
		HelloWorld::randomAddEnemyPos(0.0);
	}
}
