#pragma once

#ifndef COMBO
#define COMBO

#include "cocos2d.h"
USING_NS_CC;
#include "GameProtocol.h"

struct comboInfo
{
	int socre;
	Vec2 pos;
};

class Combo :public GameProtocol
{
public:
	CREATE_FUNC(Combo);

	Combo();
	CC_SYNTHESIZE(int,_comboCount,ComboCount);

	CC_SYNTHESIZE(Label*,_comboLabel,ComboLabel);

	CC_SYNTHESIZE(Node*,_comboCaller,ComboCaller);

	void comboPlus(int value);
protected:
	int _minCount = 3;

	std::function<int(int)> comboFunction = [](int comboCount)->int {return 50 * comboCount + 10 * pow(comboCount, 2); };

	void combo();

	EventCustom _event = EventCustom("combo");

	comboInfo _info;


};

#endif // !COMBO
