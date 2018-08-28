#include "base/CCDirector.h"
USING_NS_CC;

void Director::settingPause()
{//added by mcz
	if (_paused)
	{
		return;
	}

	_oldAnimationInterval = _animationInterval;

	// when paused, don't consume CPU
	setAnimationInterval(1 / 60.0f);
	_paused = true;
}

