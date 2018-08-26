#pragma once

#ifndef CONFIG
#define CONFIG

#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include"cocos2d.h"
USING_NS_CC;

class Config:public Layer 
{
public:
	Config();

	CREATE_FUNC(Config);

protected:
	virtual bool init()override;


};

#endif // !CONFIG
