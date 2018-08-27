#pragma once

#ifndef TITLESCENE
#define TITLESCENE

#include "AppDelegate.h"

#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include "Config.h"

#include"cocos2d.h"
USING_NS_CC;



class TitleScene:public Layer
{
public:
	TitleScene();

	static Scene* createScene();

	CREATE_FUNC(TitleScene);
protected:

	virtual bool init()override;

	ui::Text *_label_start;

	ui::Text *_label_demo;

	ui::Text * _label_config;

	Size size=Director::getInstance()->getVisibleSize();

	virtual void onEnter()override;

	//virtual void onExit()override;
};
#endif // !TITLESCENE

