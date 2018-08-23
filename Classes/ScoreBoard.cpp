#include "ScoreBoard.h"

ScoreBoard::ScoreBoard() {
    
}

void ScoreBoard::addScore(int score)
{
	_score += score;
}

int ScoreBoard::getScore() const
{
	return _score;
}

void ScoreBoard::setScore(int value)
{
	if (value>_score)
	{
		_score = value;

	}
	_scoreOnShow = value;
}

bool ScoreBoard::init()
{
	if (!GameProtocol::init())
	{
		return false;
	}

	_updateSpeed = 6;

	_scoreLabel = Label::create("","",30);

	this->addChild(_scoreLabel);

	_title = "Score:";

	scheduleUpdate();

	return true;
}

void ScoreBoard::update(float dt)
{
	if (_scoreOnShow>_score)
	{
		_scoreOnShow = _score;
	}
	else //_scoreOnShow <= _score
	{
		if (_scoreOnShow>=_score-_updateSpeed)
		{
			_scoreOnShow = _score;
		}
		else
		{
			_scoreOnShow += _updateSpeed;
		}
	}

	_scoreLabel->setString(_title + String::createWithFormat("%i",_scoreOnShow)->getCString());
}


