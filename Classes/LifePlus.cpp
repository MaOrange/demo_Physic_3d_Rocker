#include "LifePlus.h"

//LifePllus


void LifePlus::addShield(float x)
{
	currentShield += x;
	shieldUpdate();
}

void LifePlus::removeAllShield()
{
	currentShield = 0;
	shieldUpdate();
}

void LifePlus::percentUpdate()
{
	percent = (currentLife) / (maxLife + currentShield) * 100;
}

void LifePlus::damage(float x)
{
	if (x < currentShield)//the damage is no enough to break the shield
	{
		currentShield -= x;
		shieldUpdate();
	}
	else// shield break through and damage(x-currtentShield)
	{
		removeAllShield();
		Life::damage(x - currentShield);
		shieldUpdate();
	}

}

void LifePlus::recover(float x)
{
	Life::recover(x);
	percentUpdate();
	shieldUpdate();
}


LifePlus * LifePlus::creatWithMaxLife(float max, const std::string fileName)
{
	LifePlus* newLifeBar = LifePlus::create();

	if (!newLifeBar || !newLifeBar->initWithMaxLife(max, fileName))
	{
		CC_SAFE_DELETE(newLifeBar);
		return nullptr;
	}

	return newLifeBar;
}

bool LifePlus::initWithMaxLife(float max, const std::string fileName)
{
	if (!Life::initWithMaxLife(max, fileName))
	{
		return false;
	}

	//hold handle
	_shieldLB = static_cast<ui::LoadingBar*>(this->getChildren().at(0)->getChildByName(SHIELD));

	currentShield = 0;

	_shieldLB->setPercent(0);


	return true;
}

void LifePlus::setMaxLife(float x)
{
	maxLife = x;
	percentUpdate();
	effectCheck();
	shieldUpdate();
}

void LifePlus::addMaxLife(float x)
{
	currentLife += x;
	setMaxLife(getMaxLife() + x);

}

//bool LifePlus::init()
//{
//	shieldLB = static_cast<ui::LoadingBar*>(this->getChildren().at(0)->getChildByName(shield));
//	return Life::init();
//
//}



void LifePlus::shieldUpdate()
{
	percentUpdate();
	_shieldLB->setPercent(percent + (currentShield) / (maxLife + currentShield) * 100);
	_onShowLD->setPercent(percent);
	effectCheck();
}
