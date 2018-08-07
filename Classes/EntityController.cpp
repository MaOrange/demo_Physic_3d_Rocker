#include "EntityController.h"
#include "Entity.h"

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

void EntityController::onEnter()
{
	Node::onEnter();
}
