#include "Skill.h"
#include "Entity.h"

Skill::Skill() {
	_cd = 0.0f;
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
	if (_cd>0)
	{
		_skillRocker->CDStart(_cd);
	}
}

void Skill::skillDirectionCallBack(Vec2 & vec)
{
}


