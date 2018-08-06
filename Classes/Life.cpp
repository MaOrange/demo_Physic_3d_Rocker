#include "Life.h"

Life::Life() {
	
}

void Life::damage(float x)
{
	currentLife-=x;
	currentLife = (currentLife>0) ? (currentLife) : (currentLife=0);

	_onShowLD->setPercent(currentLife/maxLife*100);

	schedule(schedule_selector(Life::damageEffectCB), 1.0f / 60);

}

void Life::recover(float x)
{
	currentLife += x;
	currentLifeCheck();
	percentUpdate();

	_onShowLD->setPercent(percent);

	effectCheck();

}

Life* Life::creatWithMaxLife(float max, const std::string fileName)
{
	auto newLife = Life::create();

	newLife->initWithMaxLife(max,fileName);
	
	return newLife;
}

bool Life::initWithMaxLife(float max, const std::string fileName)
{
	//
	auto tempScene = CSLoader::createNode(fileName);

	Node* lifeRootNode = tempScene->getChildByName(ROOT);

	lifeRootNode->removeFromParent();

	lifeRootNode->setPosition(Point::ZERO);

	this->addChild(lifeRootNode);

	_rootNode = this->getChildren().at(0);

	//

	maxLife = max;

	currentLife = max;

	percentUpdate();

	_onShowLD= ((ui::LoadingBar*)_rootNode->getChildByName(ONSHOW));
		
	_onShowLD->setPercent(percent);

	_effectLD = ((ui::LoadingBar*)_rootNode->getChildByName(EFFECT));
	_effectLD->setPercent(percent);

	return true;
}

void Life::effectCheck()
{
	if (_effectLD->getPercent() < percent)
	{
		_effectLD->setPercent(percent);
	}
}

//bool Life::init()
//{
//	if (!Node::init())
//	{
//		return false;
//	}
//
//	return true;
//}

void Life::damageEffectCB(float dt)
{
	if (_onShowLD->getPercent()<_effectLD->getPercent())
	{
		_effectLD->setPercent(_effectLD->getPercent()-dt*effectSpeed);
	} 
	else
	{
		unschedule(schedule_selector(Life::damageEffectCB));
	}
	
}

void Life::percentUpdate()
{
	percent = currentLife / maxLife * 100;
}

inline void Life::currentLifeCheck()
{
	if (currentLife>maxLife)
	{
		currentLife = maxLife;
	} 
	else if(currentLife<0)
	{
		currentLife = 0;
	}
}


