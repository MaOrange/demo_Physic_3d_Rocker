#pragma once
#include"Rocker.h"

#include "cocos-ext.h"
USING_NS_CC_EXT;

#ifndef SKILLROCKER
#define SKILLROCKER

typedef  std::function<void(SkillInfo*)> SkillRockerCallBackHandle;


class SkillRocker :public Rocker
{
public:
	CREATE_FUNC(SkillRocker);

	static SkillRocker* createWith(const char * iconFile = _SKILLICON, const char * cdFile = _SKILLCD);

	virtual bool initWith(const char * iconFile, const char * cdFile);

	void setIsEnable(bool value);
	bool getIsEnable();

	void setIsNoPower(bool value);
	bool getIsNoPower();

	void CDStart(float CDtime);

	void CDReadySynchronize();//to synchronize the cd progress in skillRocker and hero

	void CDPassCallBack();

	void CDUpdate(float dt);

	void CDAdvance(float time);

	static Sprite* _cancel;

	Vec2 deltaPrev;//to save the prev delta value to be passed by ptr to skillInfo

	SkillRockerCallBackHandle OnSkillTrigerCallBack = [](SkillInfo*) {};

	//std::function<void(Vec2*)> onRockerChangeCallBack;
	

protected:
	Sprite* _skillDisabled;

	Sprite* _skillNoPower;

	Sprite * _skillOutLine;
	float CD = 0;

	float CDPassed = 0;

	bool isCD = false;

	bool isEnable = true;

	bool isNoPower = false;

	Sprite* _CDIndicator;

	ControlPotentiometer* _CDDemostrate;

	Label* _CDLabel;

	virtual bool onTouchBeginCB(Touch * touch, Event * event)override;

	virtual void onTouchMovedCB(Touch * touch, Event * event)override;

	virtual void onTouchEndedCB(Touch * touch, Event * event)override;

	SkillRockerCallBackHandle OnCDStartCallBack = [](SkillInfo*) {};

	void OnSkillTriger(SkillInfo * skillInfo);

	//for cd progress
	float senseR=0.0f;

};

#endif // !SKILLROCKER
