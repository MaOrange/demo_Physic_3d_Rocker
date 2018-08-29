#include "Skill_IcyBlast.h"
#include"GameHeader.h"

Skill_IcyBlast::Skill_IcyBlast() {
    
}

void Skill_IcyBlast::setEntityController(EntityController * controller)
{
	Skill::setEntityController(controller);

	_entityController->getEntityControlled()->addChild(_skillPos);

	_skillPos->release();

	_skillPos->setVisible(false);

	_skillPos->setCameraMask(_entityController->getEntityControlled()->getSprite3D()->getCameraMask());
}

bool Skill_IcyBlast::init()
{
	if (!Skill::init())
	{
		return false;
	}

	_pCache->addShapesWithFile("Skill/IcyBlast.plist");

	_skillPos = Sprite::create("Skill/Skill_IcyBlast.png");

	_skillPos->retain();

	_skillPos->setOpacity(100);

	_skillPos->setGlobalZOrder(-1);

	_skillRocker = SkillRocker::createWith("Skill/IcyBlast_Icon.png","Skill/IcyBlast_CD.png");

	_skillRocker->OnSkillTrigerCallBack = CC_CALLBACK_1(Skill_IcyBlast::skillTriggerCalledBack,this);

	_skillRocker->rockerOnChange = CC_CALLBACK_1(Skill_IcyBlast::skillDirectionCallBack,this);

	_targets.push_back(-1);

	_skillRocker->addChild(this);

	return true;
}

void Skill_IcyBlast::skillTriggerCalledBack(SkillInfo * info)
{
	auto effect = Sprite::create("Skill/Skill_IcyBlast.png");

	_pCache->setBodyOnSprite("Skill_IcyBlast",effect);

	effect->setGlobalZOrder(-1);

	effect->setPosition(_entityController->getEntityControlled()->getPosition()+SENSIBILITY*info->direction);

	effect->setRotation(90-CC_RADIANS_TO_DEGREES(info->direction.getAngle()));

	effect->setCameraMask(_entityController->getEntityControlled()->getSprite3D()->getCameraMask());

	_entityController->getEntityControlled()->getParent()->addChild(effect);

	auto newListener = createHitListener(effect);

	newListener->hitCallBack = [=](Node* node, Entity* target, PhysicsContactData cData)
	{
		target->getLifeBar()->damage(20.0f);
		hit(target, cData);
	};

	_dispatcher->addEventListenerWithSceneGraphPriority(newListener,effect);

	effect->setOnExitCallback([=]() {_dispatcher->removeEventListener(newListener); });

	//particle effect
	auto particle = ParticleSystemQuad::create("Particle/icyBlast.plist");

	particle->setPosition(Point::ZERO);

	particle->setCameraMask(effect->getCameraMask());

	effect->getParent()->addChild(particle);

	particle->setPosition(effect->getPosition()+Vec2(0,effect->getContentSize().width/3));

	particle->setScaleY(sqrt(2));

	particle->setAutoRemoveOnFinish(true);

	////////////////

	//action
	effect->setScale(0.01f);

	auto ext = ScaleTo::create(0.3f,1.0f);

	auto dis = CallFunc::create([=]() {effect->removeFromParentAndCleanup(true); });

	auto combo = Sequence::create(ext, dis, NULL);

	effect->runAction(combo);
}

void Skill_IcyBlast::skillDirectionCallBack(Vec2 & vec)
{
	if (vec.length()==0)
	{
		_skillPos->setVisible(false);
	}
	else//should move
	{
		_skillPos->setVisible(true);
		_skillPos->setPosition(SENSIBILITY*vec);
		_skillPos->setRotation(90 - CC_RADIANS_TO_DEGREES(vec.getAngle()));
	}
}

void Skill_IcyBlast::hit(Entity* entity, PhysicsContactData cData)
{
	auto hit = ParticleSystemQuad::create("Particle/blastHit.plist");

	hit->setPosition(cData.points[0]);

	hit->setRotation(180-CC_RADIANS_TO_DEGREES(cData.normal.getAngle()));

	hit->setCameraMask(_entityController->getEntityControlled()->getSprite3D()->getCameraMask());

	_entityController->getEntityControlled()->getParent()->addChild(hit);

	hit->setAutoRemoveOnFinish(true);

	playEffect(ICYBLAST_HIT);
}
