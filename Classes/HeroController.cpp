#include "HeroController.h"

HeroController::HeroController() {
    
}

void HeroController::update(float dt)
{
	_entity->setEntityVelocity(_heroVelocity);
}

void HeroController::onEnter()
{
	scheduleUpdate();
}

void HeroController::onExit()
{
	unscheduleUpdate();
}



void HeroController::setRocker(Rocker * rocker)
{
	_rocker = rocker;

	_rocker->rockerOnChange = CC_CALLBACK_1(HeroController::setHeroVelocity, this);
}
