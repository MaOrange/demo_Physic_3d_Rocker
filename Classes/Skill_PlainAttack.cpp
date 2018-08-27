#include "Skill_PlainAttack.h"
#include "EntityController.h"

Skill_PlainAttack::Skill_PlainAttack() {
    
}

void Skill_PlainAttack::setEntityController(EntityController * controller)
{
	Skill::setEntityController(controller);

	this->getEntityController()->getEntityControlled()->addChild(_skillDirection);

	_skillDirection->setCameraMask(getEntityController()->getEntityControlled()->getSprite3D()->getCameraMask());

	_skillDirection->release();

	_skillDirection->setVisible(false);

	_skillDirection->setAnchorPoint(Vec2 (0,0.5));

	hitCallBack = [=](Node* node,Entity*entity, PhysicsContactData cData) 
	{
		entity->getLifeBar()->damage(DAMAGE); 
		hitEffect(cData.points[0],entity); 
	};
}

bool Skill_PlainAttack::init()
{
	if (!Skill::init())
	{
		return false;
	}

	_textureCache->addImage("Skill/PlainAttackRocket.png");

	_physicsCache->addShapesWithFile("Skill/SkillRocket.plist");

	_skillRocker = SkillRocker::createWith("Skill/PlainAttack_Icon.png","Skill/PlainAttack_CD.png");

	_skillRocker->OnSkillTrigerCallBack = CC_CALLBACK_1(Skill_PlainAttack::skillTriggerCalledBack,this);

	_skillRocker->rockerOnChange=CC_CALLBACK_1(Skill_PlainAttack::skillDirectionCallBack,this);
	//
	_skillRocker->addChild(this);

	///_skillDirection
	_skillDirection = Sprite::create("Skill/SkillDirection.png");

	_skillDirection->setGlobalZOrder(-1);

	_skillDirection->retain();///////

	_targets.push_back(-1);

	return true;
}

void Skill_PlainAttack::skillTriggerCalledBack(SkillInfo *skillInfo)
{
	auto newRocket = Sprite::createWithTexture(_textureCache->addImage("Skill/PlainAttackRocket.png"));

	_physicsCache->setBodyOnSprite("PlainAttackRocket",newRocket);

	this->getEntityController()->getEntityControlled()->getParent()->addChild(newRocket);

	auto tempPos = _entityController->getEntityControlled()->getPosition();

	newRocket->setGlobalZOrder(-1);

	newRocket->setPosition(tempPos);

	newRocket->setCameraMask(getEntityController()->getEntityControlled()->getSprite3D()->getCameraMask());

	newRocket->getPhysicsBody()->setContactTestBitmask(0x01);

	newRocket->getPhysicsBody()->setCategoryBitmask(0x02);

	newRocket->setScale(0.6f);

	//particle
	auto plainA = ParticleSystemQuad::create("Particle/plainAttack.plist");
	newRocket->addChild(plainA);
	plainA->setGlobalZOrder(100);
	plainA->setCameraMask(plainA->getParent()->getCameraMask());
	plainA->setPosition(Point::ZERO);
	//plainA->setTexture(_textureCache->addImage("Particle/ice_texture.png"));
	plainA->setCascadeOpacityEnabled(false);
	////

	//newRocket shoot and destroy itself
	Vec2 tempVec = skillInfo->direction;

	newRocket->setRotation(-CC_RADIANS_TO_DEGREES(tempVec.getAngle()));

	auto move = MoveBy::create(ATTACKRANGE/ROCKETSPEED,tempVec*ATTACKRANGE/tempVec.length());

	auto vis = CallFunc::create([=]() 
	{
		newRocket->setOpacity(0);
		
		newRocket->getPhysicsBody()->removeFromWorld();
		
		plainA->stopSystem();
	});

	auto wait = DelayTime::create(2.0f);

	auto des = CallFunc::create(CC_CALLBACK_0(Skill_PlainAttack::destroy,this,newRocket));

	auto comb = Sequence::create(move,vis,wait,des,NULL);

	newRocket->runAction(comb);
	//listener for new rocket
	//auto newListener = createListener(newRocket);

	

	auto newListener = createHitListener(newRocket);

	newRocket->setOnExitCallback([=]() {_dispatcher->removeEventListener(newListener); });

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
				//CCLOG("%x",&contact);
			}
		}
		else if (contact.getShapeB()->getBody()->getOwner() == sprite)
		{
			Entity* entity = (dynamic_cast<Entity*>(contact.getShapeA()->getBody()->getOwner()));
			if (entity && entity->getTeamFlag() == -1)
			{
				entity->getLifeBar()->damage(DAMAGE);
				//CCLOG("%x", &contact);
			}
		}
		return false;
	};

	return newListener;

}

void Skill_PlainAttack::skillDirectionCallBack(Vec2 & vec)
{
	if (vec.length()==0)
	{
		_skillDirection->setVisible(false);

	}
	else//vec.length()!=0
	{
		_skillDirection->setVisible(true);

		_skillDirection->setRotation(-CC_RADIANS_TO_DEGREES(vec.getAngle()));
	}
}

void Skill_PlainAttack::hitEffect(Vec2 pos, Entity* entity)
{
	auto newHit = ParticleSystemQuad::create("Particle/hit.plist");

	newHit->setCameraMask(getEntityController()->getEntityControlled()->getSprite3D()->getCameraMask());

	entity->getParent()->addChild(newHit);

	newHit->setPosition(pos);

	newHit->setRotation(CCRANDOM_0_1()*360);

	newHit->setAutoRemoveOnFinish(true);

	//experimental::AudioEngine::play2d(,false,Config::getEffectVol());

	SimpleAudioEngine::getInstance()->playEffect("Audio/SWORD05.WAV");
}
