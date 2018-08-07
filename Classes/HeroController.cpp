#include "HeroController.h"
#include "Entity.h"

HeroController::HeroController() {
    
}

void HeroController::update(float dt)
{
	_entityControlled->setEntityVelocity(_heroVelocity);

	CCLOG("_heroVelocity: %3.f, %3.f",_heroVelocity.x,_heroVelocity.y);
}

void HeroController::onEnter()
{
	//EntityController::onEnter();
	Node::onEnter();

	scheduleUpdate();
}

void HeroController::onExit()
{

	unscheduleUpdate();
	
	EntityController::onExit();
}

bool HeroController::init()
{

	return true;
}

void HeroController::setRocker(Rocker * rocker)
{
	_rocker = rocker;

	_rocker->rockerOnChange = CC_CALLBACK_1(HeroController::setHeroVelocity, this);
}
