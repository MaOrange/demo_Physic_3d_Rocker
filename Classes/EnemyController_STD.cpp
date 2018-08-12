#include "EnemyController_STD.h"

EnemyController_STD::EnemyController_STD() {
	_animation = nullptr;
	_animate_move = nullptr;
	_animate_attack = nullptr;
	_animate_die= nullptr;
	_attackTarget = nullptr;
}

EnemyController_STD::~EnemyController_STD()
{
	CC_SAFE_RELEASE_NULL(_animation);

	CC_SAFE_RELEASE_NULL(_animate_move);

	CC_SAFE_RELEASE_NULL(_animate_attack);

	CC_SAFE_RELEASE_NULL(_animate_die);
}

void EnemyController_STD::update(float dt)
{
	switch (_enemyState)
	{
	case hunting:
		_huntTimer += dt;
		if (isInRange())//in attack range
		{
			attack(findDelta());
			_enemyState = attacking;
		}
		else
		{
			while (_huntTimer >= HUNT_PACE)
			{
				_huntTimer -= HUNT_PACE;

				auto delta = findDelta();
				//update hunt target
				_enemyVelocity = Vec2(SPEED*delta.x/delta.length(), SPEED*delta.y/delta.length());
			}
		}
		_entityControlled->setEntityVelocity(_enemyVelocity);
		break;
	case attacking:
		_attackTimer += dt;
		if (_attackTimer>=2)//50.0f/60
		{
			_attackTimer = 0;
			//_enemyState = hunting;
		}
		
		break;
	case dead:
		break;
	default:
		break;
	}
}

void EnemyController_STD::setEntityControlled(Entity * entity)
{
	EntityController::setEntityControlled(entity);

	entity->setTeamFlag(-1);
}


bool EnemyController_STD::init()
{
	if (!EntityController::init())
	{
		
		return false;
	}


	setAnimation(Animation3D::create(ENEMY_FILE));

	setAnimate_move(RepeatForever::create(Animate3D::create(_animation, MOVE_ANIMATE_BEGIN, MOVE_ANIMATE_END- MOVE_ANIMATE_BEGIN)));

	setAnimate_attack(Animate3D::create(_animation, ATTACK_ANIMATE_BEGIN, ATTACK_ANIMATE_END- ATTACK_ANIMATE_BEGIN));

	setAnimate_die(Animate3D::create(_animation, DIE_ANIMATE_BEGIN, DIE_ANIMATE_END- DIE_ANIMATE_BEGIN));

	_textureCache->addImage(_ATTACKEFFECT);

	_physicsCache->addShapesWithFile(_ATTACKEFFECT_PHYSICS);

	_enemyState = hunting;

	return true;
}

bool EnemyController_STD::isInRange()
{

	float dis = findDelta().getLength();

	return dis <= 30;//default attack range 30
}

Vec2 EnemyController_STD::findDelta()
{
	auto p1 = convertToNodeSpace(getEntityControlled()->getPosition());

	auto p2 = convertToNodeSpace(_attackTarget->getPosition());

	return (p2-p1);
}

void EnemyController_STD::attack(Vec2 dir)
{
	CCLOG("attack");
	_entityControlled->getSprite3D()->setRotation(-CC_RADIANS_TO_DEGREES(dir.getAngle()));

	_enemyVelocity = Point::ZERO;
	//attack effect
	auto effect = Sprite::createWithTexture(_textureCache->addImage(_ATTACKEFFECT));

	_physicsCache->setBodyOnSprite("EnemyAttack_close",effect);

	effect->setScaleX(0.1f);

	effect->setAnchorPoint(Vec2(0, 0.5f));

	effect->setCameraMask(getEntityControlled()->getSprite3D()->getCameraMask());

	_entityControlled->addChild(effect);

	Sequence* combo;

	auto attackForward = ScaleTo::create(1.0f/3, 1.0f, 1.0f);

	auto destory = CallFunc::create([=]() {effect->removeFromParentAndCleanup(true); _enemyState = hunting;});

	combo = Sequence::create(attackForward,destory,NULL);

	effect->runAction(combo);

	//entity animation
	_entityControlled->getSprite3D()->runAction(_animate_attack);

}