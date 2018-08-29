#include "HeroController.h"
#include "Entity.h"

HeroController::HeroController() 
{
	_animation = nullptr;
	_animate_Move = nullptr;
	_animate_Move_Forever = nullptr;
	_animate_Die = nullptr;
}

HeroController::~HeroController()
{
	CC_SAFE_RELEASE_NULL(_animation);

	CC_SAFE_RELEASE_NULL(_animate_Move);

	CC_SAFE_RELEASE_NULL(_animate_Move_Forever);

	CC_SAFE_RELEASE_NULL(_animate_Die);
}

void HeroController::update(float dt)
{
	if (_entityControlled->getLifeBar()->getCurrentLife()<=0)
	{
		_entityControlled->setEntityVelocity(Point::ZERO);

		_entityControlled->entityDie();

		_entityControlled->getSprite3D()->stopAllActions();

		_entityControlled->getSprite3D()->runAction(_animate_Die);
	}
	else
	{
		_entityControlled->setEntityVelocity(2*_heroVelocity);
		
		//CCLOG("_heroVelocity: %3.f, %3.f",_heroVelocity.x,_heroVelocity.y);
	}
}

void HeroController::onEnter()
{
	//EntityController::onEnter();
	EntityController::onEnter();

	scheduleUpdate();
}

void HeroController::onExit()
{
	unscheduleUpdate();
	
	EntityController::onExit();
}

void HeroController::rockerChange(Vec2 vec)
{
	
	//Animation

	if (vec.length()!=0)//moving
	{
		setHeroVelocity(vec/vec.length()*HEROVELOCITY);
		if (!_entityControlled->getSprite3D()->getActionByTag(HeroAnimationTag::move))
		{
			_entityControlled->getSprite3D()->runAction(_animate_Move_Forever);
		}
	}
	else//not moving
	{
		setHeroVelocity(Point::ZERO);
		if (auto action=_entityControlled->getSprite3D()->getActionByTag(HeroAnimationTag::move))
		{
			_entityControlled->getSprite3D()->stopAction(action);
		}
	}

	
}

bool HeroController::init()
{
	setAnimation(Animation3D::create("3D/HeroAnimation2.c3b"));
	
	setAnimate_Move(Animate3D::createWithFrames(_animation,0,120,60.0f));

	_animate_Move->setSpeed(2.0f);

	//_animate_Move->setQuality(cocos2d::Animate3DQuality::QUALITY_HIGH);

	setAnimation_Move_Forever(RepeatForever::create(_animate_Move));

	_animate_Move_Forever->setTag(HeroAnimationTag::move);

	auto tempA = Animation3D::create("3D/HeroAnimation_die.c3b");

	setAnimate_Die(Animate3D::createWithFrames(tempA,0,40,60.0f));

	if (!_animation || !_animate_Move || !_animate_Die)
	{
		return false;
	}

	return true;
}


void HeroController::setEntityControlled(Entity * entity)
{
	EntityController::setEntityControlled(entity);

	entity->setTeamFlag(1);
}

void HeroController::setRocker(Rocker * rocker)
{
	_rocker = rocker;

	_rocker->rockerOnChange = CC_CALLBACK_1(HeroController::rockerChange, this);
}
