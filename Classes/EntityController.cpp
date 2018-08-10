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
	scheduleUpdate();
}

void EntityController::damage(float value)
{
	this->getEntityControlled()->getLifeBar()->damage(value);
}

void EntityController::recover(float value)
{
	this->getEntityControlled()->getLifeBar()->recover(value);
}
