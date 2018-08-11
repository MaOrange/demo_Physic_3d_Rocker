#include "Wall.h"

Wall::Wall() {
    
}

bool Wall::init()
{
	if (!Node::init())
	{
		return false;
	}

	isWall = true;

	return true;
}
