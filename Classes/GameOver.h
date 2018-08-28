#pragma once

#ifndef GAMEROVER
#define GAMEOVER

#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include"cocos2d.h"
#include "SceneManager.h"
#include"GameHeader.h"
#include"ScoreBoard.h"
USING_NS_CC;

using namespace ui;

class GameOver :public Layer
{
public:
	GameOver();

	CREATE_FUNC(GameOver);

	static GameOver* createWithScore(int score);
protected:
	//virtual bool init()override;

	bool initWithScore(int score);

};
#endif // !GAMEROVER

