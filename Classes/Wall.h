#pragma once


#ifndef WALL
#define WALL

#include"cocos2d.h"

USING_NS_CC;

class Wall :public Node
{
public:
	Wall();
	CREATE_FUNC(Wall);
protected:
	CC_SYNTHESIZE(bool, isWall,IsWall);

	virtual bool init()override;

};

#endif // !WALL
