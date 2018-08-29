#include "ScoreBoard.h"

ScoreBoard::ScoreBoard() {
    
}

ScoreBoard * ScoreBoard::createWithLabel(Label * label)
{
	if (!label)
	{
		return nullptr;
	}

	auto scoreBoard = create();

	scoreBoard->initWithLabel(label);

	return scoreBoard;
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
		_scoreOnShow = value;

	}
	_score = value;
}


bool ScoreBoard::initWithLabel(Label * label)
{
	_updateSpeed = 6;

	_scoreLabel =label;

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
		if (_scoreOnShow>=_score-_updateSpeed*dt)
		{
			_scoreOnShow = _score;
		}
		else
		{
			_scoreOnShow += _updateSpeed*dt;
		}
	}

	_scoreLabel->setString(_title + String::createWithFormat("%i",_scoreOnShow)->getCString());
}


