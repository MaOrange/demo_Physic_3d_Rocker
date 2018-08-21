#include "Skill_IcyBlock.h"

Skill_IcyBlock::Skill_IcyBlock() {
    
}

void Skill_IcyBlock::setEntityController(EntityController * controller)
{
	Skill::setEntityController(controller);

	_entityController->getEntityControlled()->addChild(_skillPos);

	_skillPos->release();

	_skillPos->setVisible(false);

	_skillPos->setCameraMask(controller->getEntityControlled()->getSprite3D()->getCameraMask());
}

void Skill_IcyBlock::skillDirectionCallBack(Vec2 & vec)
{
	if (vec.length() == 0)
	{
		_skillPos->setVisible(false);
	}
	else//should move
	{
		_skillPos->setVisible(true);
		_skillPos->setPosition(ICYBLOCK_SENSIBILITY*vec);
		_skillPos->setRotation(90 - CC_RADIANS_TO_DEGREES(vec.getAngle()));
	}
}

void Skill_IcyBlock::skillTriggerCalledBack(SkillInfo * info)
{
	auto block = Sprite3D::create("3D/IcyBlock.c3b");

	//pCache
	block->setPosition(_entityController->getEntityControlled()->getPosition() + ICYBLOCK_SENSIBILITY*info->direction);
	
	block->setPositionZ(0);

	block->setRotation(90 - CC_RADIANS_TO_DEGREES(info->direction.getAngle()));

	block->setCameraMask(_entityController->getEntityControlled()->getSprite3D()->getCameraMask());

	//action
	delayCall([=]() {block->removeFromParentAndCleanup(true); }, 5.0f);
}

bool Skill_IcyBlock::init()
{
	if (!Skill::init())
	{
		return false;
	}

	//_pCache

	_skillPos = Sprite3D::create("3D/IcyBlock.c3b");

	_skillPos->retain();

	_skillPos->setOpacity(100);

	_skillRocker = SkillRocker::createWith("Skill/IcyBlock_Icon.png","Skill/IcyBlock_CD.png");

	_skillRocker->OnSkillTrigerCallBack = CC_CALLBACK_1(Skill_IcyBlock::skillTriggerCalledBack, this);

	_skillRocker->rockerOnChange = CC_CALLBACK_1(Skill_IcyBlock::skillDirectionCallBack,this);

	_targets.push_back(-1);

	_skillRocker->addChild(this);

	return true;
}
