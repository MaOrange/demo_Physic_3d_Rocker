#include "Skill.h"
#include "Entity.h"

Skill::Skill() {
    
}

bool Skill::init()
{
	if (!GameProtocol::init())
	{
		return false;
	}

	return true;
}

void Skill::skillTriggerCalledBack(SkillInfo *)
{
}

void Skill::skillDirectionCallBack(Vec2 & vec)
{
}


