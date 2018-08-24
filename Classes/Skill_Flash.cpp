#include "Skill_Flash.h"

Skill_Flash::Skill_Flash() {
    
}

void Skill_Flash::setEntityController(EntityController * entity)
{
	Skill::setEntityController(entity);

	entity->getEntityControlled()->addChild(_skillDir);

	_skillDir->setAnchorPoint(Vec2(0.0f, 0.5f));

	_skillDir->setVisible(false);

	_skillDir->setCameraMask(entity->getEntityControlled()->getSprite3D()->getCameraMask());

	_skillDir->release();
}

bool Skill_Flash::init()
{
	if (!Skill::init())
	{
		return false;
	}

	_skillDir = Sprite::create("Skill/SkillDirection.png");

	_skillDir->setGlobalZOrder(-1);

	_skillDir->retain();

	_skillRocker = SkillRocker::createWith("Skill/Flash_Icon.png", "Skill/Flash_CD.png");

	_skillRocker->OnSkillTrigerCallBack = CC_CALLBACK_1(Skill_Flash::skillTriggerCalledBack, this);

	_skillRocker->rockerOnChange = CC_CALLBACK_1(Skill_Flash::skillDirectionCallBack, this);

	_targets.push_back(-1);

	_skillRocker->addChild(this);

	return true;
}

void Skill_Flash::skillTriggerCalledBack(SkillInfo * info)
{
	auto entity = _entityController->getEntityControlled();

	

	if (info->direction.length()!=0)
	{
		entity->setPosition(entity->getPosition() + info->direction / info->direction.length()*FLASH_DIS);
	}
	
}

void Skill_Flash::skillDirectionCallBack(Vec2 & vec)
{
	if (vec.length() == 0)
	{
		_skillDir->setVisible(false);

	}
	else//vec.length()!=0
	{
		_skillDir->setVisible(true);

		_skillDir->setRotation(-CC_RADIANS_TO_DEGREES(vec.getAngle()));
	}
}
