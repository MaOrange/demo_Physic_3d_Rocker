#include "Skill_IcyBlast.h"

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

	_skillRocker = SkillRocker::createWith("Skill/IcyBlast_Icon.png","Skill/IcyBlast_CD.png");

	_skillRocker->OnSkillTrigerCallBack = CC_CALLBACK_1(Skill_IcyBlast::skillTriggerCalledBack,this);

	_skillRocker->rockerOnChange = CC_CALLBACK_1(Skill_IcyBlast::skillDirectionCallBack,this);

	_targets.push_back(-1);

	_skillRocker->addChild(this);

	hitCallBack = [=](Entity* target) {target->getLifeBar()->damage(20.0f); };

	return true;
}

void Skill_IcyBlast::skillTriggerCalledBack(SkillInfo * info)
{
	auto effect = Sprite::create("Skill/Skill_IcyBlast.png");

	effect->setPosition(_entityController->getEntityControlled()->getPosition()+SENSIBILITY*info->direction);

	effect->setRotation(90-CC_RADIANS_TO_DEGREES(info->direction.getAngle()));

	effect->setCameraMask(_entityController->getEntityControlled()->getSprite3D()->getCameraMask());

	_entityController->getEntityControlled()->getParent()->addChild(effect);

	_pCache->setBodyOnSprite("Skill_IcyBlast",effect);

	auto newListener = createHitListener(effect);

	_dispatcher->addEventListenerWithSceneGraphPriority(newListener,effect);

	effect->setOnExitCallback([=]() {_dispatcher->removeEventListener(newListener); });

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
