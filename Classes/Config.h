#pragma once

#ifndef CONFIG
#define CONFIG

#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include"cocos2d.h"
USING_NS_CC;
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

#include "GameHeader.h"

using namespace ui;


class Config:public Layer 
{
public:
	Config();

	CREATE_FUNC(Config);

	static float getEffectVol();

	static bool getIsEffect();

	static bool getIsBGM();

	static void setEffectVol(float value);

	static void setBGMVol(float value);

	static void setIsEffect(bool value);

	static void setIsBGM(bool value);
protected:
	virtual bool init()override;

	ui::CheckBox* _CB_Effect;

	ui::CheckBox* _CB_BGM;

	ui::Slider* _slider_effect;

	ui::Slider* _slider_BGM;

	ui::Text* _tBack;

	ui::Text* _tApply;

	ui::Text* _tTitle;

	static bool _isEffect;

	static bool _isBGM;

	static float _effect_vol;

	static float _BGM_vol;

	void effectSilderCB(Ref*pSender, ui::SliderEventType type);

	void BGMSliderCB(Ref*pSender, ui::SliderEventType type);

	void effectCBCB(Ref *pSender, ui::CheckBoxEventType eventtype);

	void BGMCBCB(Ref *pSender, ui::CheckBoxEventType eventtCCype);

	virtual void onEnter()override;

	virtual void onExit()override;
};

#endif // !CONFIG
