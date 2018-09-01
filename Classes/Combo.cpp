#pragma execution_character_set("utf-8")

#include "Combo.h"
#include "Combo.h"

Combo::Combo() {
	_comboLabel = nullptr;

	_comboCount = 0;
}

void Combo::combo()
{
	if (!_comboLabel)
	{
		_comboLabel = Label::create(String::createWithFormat("%d连击",_comboCount)->getCString(), "Fonts/title.ttf", 30);
		_comboLabel->setColor(Color3B::YELLOW);

		if (this->getParent() && this->getParent())
		{
			this->getParent()->getParent()->addChild(_comboLabel);

			_comboLabel->setCameraMask(_comboLabel->getParent()->getCameraMask());

			_comboLabel->setScaleY(sqrt(2));

			_comboCaller = this->getParent();

			this->retain();

			this->removeFromParentAndCleanup(false);

			_comboLabel->addChild(this);

			this->release();
		}
	}
	else
	{
		_comboLabel->setString(String::createWithFormat("%d连击", _comboCount)->getCString());
	}
	_comboLabel->stopAllActions();

	_comboLabel->setPosition(_comboCaller->getPosition()+Vec2(0,-20));

	auto moveUp = MoveBy::create(0.2f,Vec2(0,20));

	auto fadeIn = FadeIn::create(0.2f);

	auto showUP = Spawn::create(moveUp,fadeIn,NULL);

	auto stay = DelayTime::create(1.0f);

	auto event = CallFunc::create([=]() 
	{
		_comboLabel->setVisible(false);

		_info.pos = _comboLabel->getPosition();

		_info.socre = comboFunction(_comboCount);

		_event.setUserData(&_info);

		Director::getInstance()->getEventDispatcher()->dispatchEvent(&_event);
	});

	auto safe_wait = DelayTime::create(0.5f);

	auto des = CallFunc::create([=]() 
	{
		_comboLabel->removeFromParentAndCleanup(true);
	});

	auto seq = Sequence::create(showUP,stay,event,safe_wait,des,NULL);

	_comboLabel->runAction(seq);
}

void Combo::comboPlus(int value)
{
	_comboCount += value;

	if (_comboCount>=_minCount)
	{
		combo();
	}
}
