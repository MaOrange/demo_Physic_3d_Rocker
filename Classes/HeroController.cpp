#include "HeroController.h"
#include "Entity.h"

HeroController::HeroController() 
{
	_animation = nullptr;
	_animate_Move = nullptr;
	_animate_Move_Forever = nullptr;

}

HeroController::~HeroController()
{
	CC_SAFE_RELEASE_NULL(_animation);

	CC_SAFE_RELEASE_NULL(_animate_Move);

	CC_SAFE_RELEASE_NULL(_animate_Move_Forever);
}

void HeroController::update(float dt)
{
	_entityControlled->setEntityVelocity(_heroVelocity);

	//CCLOG("_heroVelocity: %3.f, %3.f",_heroVelocity.x,_heroVelocity.y);
}

void HeroController::onEnter()
{
	//EntityController::onEnter();
	Node::onEnter();

	scheduleUpdate();
}

void HeroController::onExit()
{

	unscheduleUpdate();
	
	EntityController::onExit();
}

void HeroController::rockerChange(Vec2 vec)
{
	setHeroVelocity(vec);
	//Animation

	if (vec.length()!=0)//moving
	{

		if (!_entityControlled->getSprite3D()->getActionByTag(HeroAnimationTag::move))
		{
			_entityControlled->getSprite3D()->runAction(_animate_Move_Forever);
		}
	}
	else//not moving
	{
		if (auto action=_entityControlled->getSprite3D()->getActionByTag(HeroAnimationTag::move))
		{
			_entityControlled->getSprite3D()->stopAction(action);
		}
		
	}

	

	
}

bool HeroController::init()
{
	setAnimation(Animation3D::create("3D/HeroAnimation.c3b"));
	
	setAnimate_Move(Animate3D::create(_animation, 0.0f, 1.0f));
	
	setAnimation_Move_Forever(RepeatForever::create(_animate_Move));
	
	_animate_Move_Forever->setTag(HeroAnimationTag::move);

	if (!_animation || !_animate_Move)
	{
		return false;
	}

	return true;
}

void HeroController::setRocker(Rocker * rocker)
{
	_rocker = rocker;

	_rocker->rockerOnChange = CC_CALLBACK_1(HeroController::rockerChange, this);
}
