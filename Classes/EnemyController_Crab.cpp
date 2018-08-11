#include "EnemyController_Crab.h"

EnemyController_Crab::EnemyController_Crab() {
    
}

EnemyController_Crab::~EnemyController_Crab()
{
}

void EnemyController_Crab::update(float dt)
{
	_turnTimer += dt;

	_recoverTimer += dt;

	if (_crabState==CrabState::died)//GG...
	{

	}
	else//alive: always running around, but won't recover when being attacked
	{
		while (_turnTimer >= TURNPACE)//should change velocity
		{
			_turnTimer -= TURNPACE;

			float tempA = CCRANDOM_0_1()*360;

			Vec2 tempV = Vec2(VELOCITY*cos(tempA),VELOCITY*sin(tempA));

			this->getEntityControlled()->setEntityVelocity(tempV);
		} 

		if (_crabState==CrabState::runningAround)
		{
			while (_recoverTimer>=RECOVERPACE)//can recover
			{
				_recoverTimer -= RECOVERPACE;

				this->getEntityControlled()->getLifeBar()->recover(RECOVER);
			}
		}
		
	}
}

void EnemyController_Crab::onEnter()
{
	EntityController::onEnter();
	this->getEntityControlled()->scheduleUpdate();
	scheduleUpdate();
}

void EnemyController_Crab::setEntityControlled(Entity * entity)
{
	EntityController::setEntityControlled(entity);
	entity->setTeamFlag(-1);
	entity->getPhysicsBody()->setCategoryBitmask(0x01);
}

bool EnemyController_Crab::init()
{
	if (!EntityController::init())
	{
		return false;
	}
	//init///////////////
	_crabState = CrabState::runningAround;

	

	return true;
}
