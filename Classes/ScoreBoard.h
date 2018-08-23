#pragma once

#ifndef SCOREBOARD
#define SCOREBOARD

#include"cocos2d.h"
USING_NS_CC;
#include "GameProtocol.h"

class ScoreBoard :public GameProtocol
{
public:
	ScoreBoard();

	CREATE_FUNC(ScoreBoard);

	void addScore(int score);

	int getScore()const;

	void setScore(int value);

	CC_SYNTHESIZE(int,_updateSpeed,UpdateSpeed);

	CC_SYNTHESIZE(Label*,_scoreLabel,ScoreLabel);

	CC_SYNTHESIZE(std::string,_title,Title);
protected:
	virtual bool init()override;

	virtual void update(float dt)override;

	int _scoreOnShow=0;

	int _score=0;

	
};

#endif // !SCOREBOARD
