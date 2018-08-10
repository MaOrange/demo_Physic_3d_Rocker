#include "Skill.h"

Skill::Skill() {
    
}

bool Skill::init()
{
	if (!Node::init())
	{
		return false;
	}

	return true;
}
