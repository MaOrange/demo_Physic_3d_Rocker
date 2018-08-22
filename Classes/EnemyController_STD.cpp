#include "EnemyController_STD.h"

bool EnemyController_STD::_isLoad = false;

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

void EnemyController_STD::preLoad()
{
	//Animation3DCache::getInstance()->addAnimation("EnemyAnimation",Animation3D::create(ENEMY_FILE));

	PhysicsShapeCache::getInstance()->addShapesWithFile(_ATTACKEFFECT_PHYSICS);

	Director::getInstance()->getTextureCache()->addImage(_ATTACKEFFECT);

	_isLoad = true;
}

void EnemyController_STD::update(float dt)
{
	if (_enemyState!=dead)
	{
		if (_entityControlled->getLifeBar()->getCurrentLife() <= 0)
		{
			_enemyState = dead;

			_entityControlled->entityDie();

			//dead call
			_entityControlled->getSprite3D()->stopAllActions();

			_entityControlled->getSprite3D()->runAction(_animate_die);

			_entityControlled->setEntityVelocity(Point::ZERO);
		}
	}
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

	if (!_isLoad)
	{
		preLoad();
	}

	setAnimation(Animation3D::create(ENEMY_FILE));

	setAnimate_move(RepeatForever::create(Animate3D::create(_animation, MOVE_ANIMATE_BEGIN, MOVE_ANIMATE_END- MOVE_ANIMATE_BEGIN)));

	setAnimate_attack(Animate3D::createWithFrames(_animation, 100, 150,60));

	_animate_attack->setSpeed(2.0f);

	setAnimate_die(Animate3D::createWithFrames(_animation, 160, 180,60));

	_enemyState = hunting;

	_targets.push_back(1);

	return true;
}

bool EnemyController_STD::isInRange()
{

	float dis = findDelta().getLength();

	return dis <= RANGE;//default attack range 30
}

Vec2 EnemyController_STD::findDelta()
{
	auto p1 = convertToNodeSpace(getEntityControlled()->getPosition());

	auto p2 = convertToNodeSpace(_attackTarget->getPosition());

	return (p2-p1);
}

void EnemyController_STD::attack(Vec2 dir)
{
	//CCLOG("attack");
	_entityControlled->getSprite3D()->setRotation(-CC_RADIANS_TO_DEGREES(dir.getAngle())+90);

	_enemyVelocity = Point::ZERO;
	//attack effect
	auto effect = Sprite::createWithTexture(_textureCache->addImage(_ATTACKEFFECT));

	_physicsCache->setBodyOnSprite("EnemyAttack_close",effect);

	_entityControlled->getSprite3D()->addChild(effect);

	effect->getPhysicsBody()->setCategoryBitmask(0x02);

	effect->getPhysicsBody()->setCollisionBitmask(0x00000000);

	effect->getPhysicsBody()->setContactTestBitmask(0x01);

	//effect->getPhysicsBody()->setGroup(1);

	effect->setScaleX(0.03f);

	effect->setAnchorPoint(Vec2(0, 0.5f));

	effect->setCameraMask(getEntityControlled()->getSprite3D()->getCameraMask());

	effect->setRotation(-90);//offset

	Sequence* combo;

	auto attackForward = ScaleTo::create(1.0f/3, 1.0f, 1.0f);

	auto destory = CallFunc::create([=]() {effect->removeFromParentAndCleanup(true); if(_enemyState==attacking)_enemyState = hunting;});

	combo = Sequence::create(attackForward,destory,NULL);

	effect->runAction(combo);

	//entity animation
	_entityControlled->getSprite3D()->stopAllActions();
	_entityControlled->getSprite3D()->runAction(_animate_attack);

	//auto newListener = createListener(effect);
	auto newListener = createHitListener(effect);

	hitCallBack = [=](Entity* entity) 
	{
		entity->getLifeBar()->damage(STD_DAMAGE);
	};

	_dispatcher->addEventListenerWithSceneGraphPriority(newListener,effect);

	effect->setOnExitCallback([=]() {Director::getInstance()->getEventDispatcher()->removeEventListener(newListener); });

	//_dispatcher->addEventListenerWithFixedPriority(newListener,1);
}

EventListenerPhysicsContact * EnemyController_STD::createListener(Sprite* sprite)
{
	auto newListener = EventListenerPhysicsContact::create();

	newListener->onContactBegin = [=](PhysicsContact & contact)->bool 
	{
		if (contact.getShapeA()->getBody()->getOwner() == sprite)
		{
			//CCLOG("effect contact!");
			Entity* entity = (dynamic_cast<Entity*>(contact.getShapeB()->getBody()->getOwner()));
			if (entity && entity->getTeamFlag() == 1)
			{
				entity->getLifeBar()->damage(STD_DAMAGE);
				return true;
				//CCLOG("%x",&contact);
			}
		}
		else if (contact.getShapeB()->getBody()->getOwner() == sprite)
		{
			Entity* entity = (dynamic_cast<Entity*>(contact.getShapeA()->getBody()->getOwner()));
			if (entity && entity->getTeamFlag() == 1)
			{
				entity->getLifeBar()->damage(STD_DAMAGE);
				//CCLOG("%x", &contact);
				return true;
			}
		}
		return false;
	};

	return newListener;
	
}
