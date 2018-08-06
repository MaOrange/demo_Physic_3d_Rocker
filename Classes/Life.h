#pragma once



#ifndef LIFE
#define LIFE
#include"cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
USING_NS_CC;

#define BACKGROUND "lifeBackground_P"
#define EFFECT "lifeEffect_LB"
#define ONSHOW "lifeOnShow_LB"
#define FRAME "lifeFrame_P"
#define ROOT "lifeRootNode"



class Life:public Node
{
public:
	Life();

	virtual void damage(float x);

	virtual void recover(float x);

	void restart(float x);

	CC_SYNTHESIZE(float,percent,Percnet);
	CC_SYNTHESIZE(float, maxLife, MaxLife);
	CC_SYNTHESIZE(float, currentLife, CurrentLife);

	CREATE_FUNC(Life);

	static Life* creatWithMaxLife(float max, const std::string fileName);

	bool initWithMaxLife(float max, const std::string fileName);

	void effectCheck();

	//virtual bool init();

protected:
	/*float percent;
	float maxLife;
	float currentLife;*/

	ui::LoadingBar* _onShowLD;

	ui::LoadingBar* _effectLD;

	Node* _rootNode;

	void damageEffectCB(float dt);

	const float effectSpeed=20;

	virtual inline void percentUpdate();

	inline void currentLifeCheck();
};


#endif // !LIFE
