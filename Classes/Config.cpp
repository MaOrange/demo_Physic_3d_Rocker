#include "Config.h"

#include"HelloWorldScene.h"
#include"TitleScene.h"

bool Config::_isEffect = true;

bool Config::_isBGM = true;

float Config::_effect_vol=1.0f;

float Config::_BGM_vol = 1.0f;

Config::Config() {
    
}

float Config::getEffectVol()
{
	return _effect_vol;
}

bool Config::getIsEffect()
{
	return _isEffect;
}

bool Config::getIsBGM()
{
	return _isBGM;
}

bool Config::init()
{
	if (!Layer::init())//2 seconds after first sound play
	{
		return false;
	}

	auto rootNode = CSLoader::createNode("Config.csb");

	this->addChild(rootNode);

	auto panel = (ui::Layout*)rootNode->getChildByName("Panel_1");

	_CB_Effect = (ui::CheckBox*)panel->getChildByName("CheckBox_1");

	_CB_BGM = (ui::CheckBox*)panel->getChildByName("CheckBox_2");

	_slider_effect = (ui::Slider*)panel->getChildByName("Slider_1");

	_slider_BGM = (ui::Slider*)panel->getChildByName("Slider_1_0");

	//config init
	_slider_BGM->setPercent(_BGM_vol * 100);

	_slider_effect->setPercent(_effect_vol * 100);

	_CB_Effect->setSelectedState(_isEffect);

	_CB_BGM->setSelectedState(_isBGM);

	_slider_effect->addEventListenerSlider(this, sliderpercentchangedselector(Config::effectSilderCB));

	_slider_BGM->addEventListenerSlider(this, sliderpercentchangedselector(Config::BGMSliderCB));

	_CB_BGM->addEventListenerCheckBox(this, checkboxselectedeventselector(Config::BGMCBCB));

	_CB_Effect->addEventListenerCheckBox(this, checkboxselectedeventselector(Config::effectCBCB));

	//blocker
	Node* node = panel->getChildByName("void");

	auto newListener = EventListenerTouchOneByOne::create();

	newListener->onTouchBegan = [](Touch* touch,Event* event) {return true; };

	newListener->setSwallowTouches(true);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(newListener,node);

	node->setOnExitCallback([=]() {Director::getInstance()->getEventDispatcher()->removeEventListener(newListener); });

	//buttons
	_tBack = (ui::Text*)panel->getChildByName("Text_back");

	_tApply = (ui::Text*)panel->getChildByName("Text_apply");

	_tTitle= (ui::Text*)panel->getChildByName("Text_title");

	return true;
}

void Config::effectSilderCB(Ref * pSender, ui::SliderEventType type)
{
	if (type == ui::SLIDER_PERCENTCHANGED)
	{
		ui::Slider* pSlider = (ui::Slider*)pSender;
		float percent = pSlider->getPercent();

		SimpleAudioEngine::getInstance()->setEffectsVolume(percent/100);

		_effect_vol = percent / 100;
	}
}

void Config::BGMSliderCB(Ref * pSender, ui::SliderEventType type)
{
	if (type == ui::SLIDER_PERCENTCHANGED)
	{
		ui::Slider* pSlider = (ui::Slider*)pSender;
		float percent = pSlider->getPercent();
		
		if(_isBGM)
		{
			SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(percent / 100);
		}

		_BGM_vol = percent / 100;

	}
}

void Config::effectCBCB(Ref * pSender, ui::CheckBoxEventType eventtype)
{
	switch (eventtype)
	{

	case ui::CheckBoxEventType::CHECKBOX_STATE_EVENT_SELECTED:
		//CCLOG("you select");
		_isEffect = true;
		SimpleAudioEngine::getInstance()->setEffectsVolume(_effect_vol);
		break;

	case ui::CheckBoxEventType::CHECKBOX_STATE_EVENT_UNSELECTED:
		//CCLOG("you unselect");
		_effect_vol = SimpleAudioEngine::getInstance()->getBackgroundMusicVolume();

		SimpleAudioEngine::getInstance()->setEffectsVolume(0.0f);

		_isEffect = false;
		break;
	default:
		break;
	}
}

void Config::BGMCBCB(Ref * pSender, ui::CheckBoxEventType eventtype)
{
	switch (eventtype)
	{

	case ui::CheckBoxEventType::CHECKBOX_STATE_EVENT_SELECTED:
		//CCLOG("you select");
		_isBGM= true;
		SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(_BGM_vol);
		break;

	case ui::CheckBoxEventType::CHECKBOX_STATE_EVENT_UNSELECTED:
		CCLOG("BGM false");

		_BGM_vol = SimpleAudioEngine::getInstance()->getBackgroundMusicVolume();

		SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.0f);

		_isBGM = false;
		break;
	default:
		break;
	}
}

void Config::onEnter()
{
	Layer::onEnter();

	if (dynamic_cast<TitleScene*>(this->getParent()))//at title
	{
		_tApply->setVisible(true);

		_tApply->addClickEventListener([=](Ref* psender)
		{
			this->removeFromParentAndCleanup(true);
		});
	}
	else//at main Game
	{
		_tBack->setVisible(true);
		_tTitle->setVisible(true);

		_tBack->addClickEventListener([=](Ref* psender)
		{
			this->removeFromParentAndCleanup(true);
		});

		_tTitle->addClickEventListener([=](Ref* psender)
		{
			SceneManager::getInstance()->toTitleScene();
		});
	}

}
