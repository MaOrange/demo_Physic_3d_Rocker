#include "Skill_PlainAttack.h"
#include "EntityController.h"

Skill_PlainAttack::Skill_PlainAttack() {
    
}

bool Skill_PlainAttack::init()
{
	if (!Skill::init())
	{
		return false;
	}

	_textureCache->addImage("Skill/PlainAttackRocket.png");

	_physicsCache->addShapesWithFile("Skill/SkillRocket.plist");

	_skillRocker = SkillRocker::createWith("");

	_skillRocker->OnSkillTrigerCallBack = CC_CALLBACK_1(Skill_PlainAttack::skillTriggerCalledBack,this);

	//
	_skillRocker->addChild(this);

	return true;
}

void Skill_PlainAttack::skillTriggerCalledBack(SkillInfo *skillInfo)
{
	auto newRocket = Sprite::createWithTexture(_textureCache->addImage("Skill/PlainAttackRocket.png"));

	_physicsCache->setBodyOnSprite("PlainAttackRocket",newRocket);

	this->getEntityController()->getEntityControlled()->addChild(newRocket);

	newRocket->setCameraMask(getEntityController()->getEntityControlled()->getSprite3D()->getCameraMask());

	newRocket->getPhysicsBody()->setContactTestBitmask(0x01);

	newRocket->getPhysicsBody()->setCategoryBitmask(0x02);

	newRocket->setScale(0.6);


	//newRocket shoot and destroy itself
	Vec2 tempVec = skillInfo->direction;

	newRocket->setRotation(-CC_RADIANS_TO_DEGREES(tempVec.getAngle()));

	auto move = MoveBy::create(ATTACKRANGE/ROCKETSPEED,tempVec*ATTACKRANGE/tempVec.length());

	auto des = CallFunc::create(CC_CALLBACK_0(Skill_PlainAttack::destroy,this,newRocket));

	auto comb = Sequence::create(move,des,NULL);

	newRocket->runAction(comb);
	//listener for new rocket
	auto newListener = createListener(newRocket);

	_dispatcher->addEventListenerWithSceneGraphPriority(newListener,newRocket);

}

void Skill_PlainAttack::destroy(Sprite * sprite)
{
	sprite->removeFromParentAndCleanup(true);
}

EventListenerPhysicsContact * Skill_PlainAttack::createListener(Sprite* sprite)
{
	auto newListener = EventListenerPhysicsContact::create();

	newListener->onContactBegin = [=](PhysicsContact & contact)->bool 
	{
		if (contact.getShapeA()->getBody()->getOwner()==sprite)
		{
			Entity* entity = (dynamic_cast<Entity*>(contact.getShapeB()->getBody()->getOwner()));
			if (entity && entity->getTeamFlag()==-1)
			{
				entity->getLifeBar()->damage(DAMAGE);
			}
		}
		else if (contact.getShapeB()->getBody()->getOwner() == sprite)
		{
			Entity* entity = (dynamic_cast<Entity*>(contact.getShapeA()->getBody()->getOwner()));
			if (entity && entity->getTeamFlag() == -1)
			{
				entity->getLifeBar()->damage(DAMAGE);
			}
		}
		return false;
	};

	return newListener;

}
