#pragma once


#ifndef LIFEPLUS
#define LIFEPLUS

#include"Life.h"

#define SHIELD "lifeShield_LB"


class LifePlus :public Life
{
public:
	void addShield(float x);

	void removeAllShield();

	void percentUpdate() override;

	void damage(float x) override;

	virtual void recover(float x)override;

	static LifePlus* creatWithMaxLife(float max, const std::string fileName);

	bool initWithMaxLife(float max, const std::string fileName);

	void setMaxLife(float x);

	void addMaxLife(float x);//add maxlife and add current life

protected:

	CREATE_FUNC(LifePlus);

	float currentShield = 0;

	ui::LoadingBar * _shieldLB;

	//bool init()override;

	void shieldUpdate();

};

#endif // !LIFEPLUS


