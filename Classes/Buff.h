#pragma once


#ifndef BUFF
#define BUFF

#include "cocos2d.h"
//#include "Entity.h"
USING_NS_CC;

class Buff:public Ref
{
public:
	Buff();

	//CREATE_FUNC(Buff);
	CC_SYNTHESIZE(std::string,_buffName,BuffName);

	CC_SYNTHESIZE(int,_teamFlag,TeamFlag);

	CC_SYNTHESIZE(float,_buffTime,BuffTime);
protected:
	virtual bool init() = 0;
	

};

#endif // !BUFF
