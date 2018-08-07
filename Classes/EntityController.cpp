#include "EntityController.h"

EntityController::EntityController() {
    
}

EntityController::~EntityController()
{
	_buffs.clear();
}

void EntityController::addBuff(Buff * buff)
{
	_buffs.pushBack(buff);	
}
