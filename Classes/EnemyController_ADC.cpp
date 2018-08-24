#include "EnemyController_ADC.h"

EnemyController_ADC::EnemyController_ADC() {
    
}

bool EnemyController_ADC::init()
{
	if (!EnemyController_STD::init())
	{
		return false;
	}

	_state = runningAttack;

	hitCallBack = CC_CALLBACK_3(EnemyController_ADC::hitCalledBack,this);

	return true;
}

void EnemyController_ADC::attack(Vec2 dir)
{
	auto rocket = ParticleSystemQuad::create("Particle/enemyAttack.plist");

	rocket->setPhysicsBody(PhysicsBody::createCircle(15));

	rocket->setCameraMask(_entityControlled->getCameraMask());

	rocket->setRotation(180-CC_RADIANS_TO_DEGREES(dir.getAngle()));

	auto body = rocket->getPhysicsBody();

	body->setCategoryBitmask(0x02);

	body->setContactTestBitmask(0x01);

	rocket->setPosition(_entityControlled->getPosition());

	_entityControlled->getParent()->addChild(rocket);

	auto newListener = createHitListener(rocket);

	_dispatcher->addEventListenerWithSceneGraphPriority(newListener,rocket);

	rocket->setOnExitCallback([=]() {_dispatcher->removeEventListener(newListener); });

	auto fly = MoveBy::create(3 * dir.length() / ROCKER_SPEED, 3 * dir);

	auto des = CallFunc::create([=]() {rocket->removeFromParentAndCleanup(true); });

	auto combo = Sequence::create(fly, des, NULL);

	rocket->runAction(combo);

	//animation
	_entityControlled->getSprite3D()->stopAllActions();

	_entityControlled->getSprite3D()->runAction(_animate_attack);
	
}

void EnemyController_ADC::update(float dt)
{
	if (_state!=adcDead && _entityControlled->getLifeBar()->getCurrentLife()<=0)
	{
		_entityControlled->getSprite3D()->stopAllActions();
		_entityControlled->getSprite3D()->runAction(_animate_die);
		
		_state = adcDead;

		_entityControlled->entityDie();
	}


	switch (_state)
	{
	case adcDead:
		break;
	case runningAttack:
		_attackTimer += dt;

		while (_attackTimer>=ADC_ATTACK_PACE)//should attack and change move dir
		{
			_attackTimer -= ADC_ATTACK_PACE;

			auto tempV = findDelta();

			attack(tempV);

			turnDirection(tempV);
		}
		break;
	default:
		break;
	}

}

void EnemyController_ADC::turnDirection(Vec2 vec)
{
	auto tempV = Vec2(vec.y,vec.x);

	tempV *= ADC_SPEED/tempV.length();

	_entityControlled->setEntityVelocity(tempV);
}

void EnemyController_ADC::hitCalledBack(Node* node,Entity* entity, PhysicsContactData cData)
{
	entity->getLifeBar()->damage(10);

	auto exp1 = ParticleSystemQuad::create("Particle/enemyExp2.plist");

	exp1->setAutoRemoveOnFinish(true);

	exp1->setPosition(node->getPosition());

	node->getParent()->addChild(exp1);

	exp1->setScale(0.5f);

	exp1->setCameraMask(node->getCameraMask());

	node->removeFromParentAndCleanup(true);
}
