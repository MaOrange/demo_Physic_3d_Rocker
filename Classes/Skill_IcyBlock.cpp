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
	auto wall = Wall::create();

	auto block = Sprite3D::create("3D/IcyBlock.c3b");

	block->setPositionZ(0);

	wall->addChild(block);

	wall->setPhysicsBody(_pCache->createBodyWithName("icyBlock_cut"));
	//wall->setPhysicsBody(PhysicsBody::createCircle(20));

	wall->setPosition(_entityController->getEntityControlled()->getPosition() + ICYBLOCK_SENSIBILITY*info->direction);

	//
	//block->setRotation3D(Vec3(45, 0, 0));

	block->setGlobalZOrder(100);

	wall->setRotation(90 - CC_RADIANS_TO_DEGREES(info->direction.getAngle()));

	block->setCameraMask(_entityController->getEntityControlled()->getSprite3D()->getCameraMask());

	_entityController->getEntityControlled()->getParent()->addChild(wall);

	//action
	delayCall([=]() {wall->removeFromParentAndCleanup(true); }, 10.0f);
}

bool Skill_IcyBlock::init()
{
	if (!Skill::init())
	{
		return false;
	}

	_pCache->addShapesWithFile("Skill/IcyBlock.plist");

	_skillPos = Sprite3D::create("3D/IcyBlock.c3b");

	_skillPos->retain();

	//_skillPos->setOpacity(170);

	_skillPos->setGlobalZOrder(100);

	_skillPos->setPositionZ(0);

	_skillRocker = SkillRocker::createWith("Skill/IcyBlock_Icon.png","Skill/IcyBlock_CD.png");

	_skillRocker->OnSkillTrigerCallBack = CC_CALLBACK_1(Skill_IcyBlock::skillTriggerCalledBack, this);

	_skillRocker->rockerOnChange = CC_CALLBACK_1(Skill_IcyBlock::skillDirectionCallBack,this);

	_targets.push_back(-1);

	_skillRocker->addChild(this);

	return true;
}
