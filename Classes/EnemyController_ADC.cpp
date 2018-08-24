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

	return true;
}

void EnemyController_ADC::attack(Vec2 dir)
{
	auto rocket = ParticleSystemQuad::create("Particle/enemyAttack.plist");

	rocket->setPhysicsBody(PhysicsBody::createCircle(15));
}

void EnemyController_ADC::update(float dt)
{
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

	_enemyVelocity = tempV;
}
