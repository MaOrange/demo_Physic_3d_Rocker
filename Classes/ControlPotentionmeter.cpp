#include "cocos-ext.h"
USING_NS_CC_EXT;

ControlPotentiometer* ControlPotentiometer::createWithSpriteFrameName(const char* backgroundFile, const char* progressFile, const char* thumbFile)
{
	ControlPotentiometer* pRet = new (std::nothrow) ControlPotentiometer();
	if (pRet != nullptr)
	{
		// Prepare track for potentiometer
		Sprite *backgroundSprite = Sprite::createWithSpriteFrameName(backgroundFile);

		// Prepare thumb for potentiometer
		Sprite *thumbSprite = Sprite::create(thumbFile);

		// Prepare progress for potentiometer
		ProgressTimer *progressTimer = ProgressTimer::create(Sprite::createWithSpriteFrameName(progressFile));
		//progressTimer.type              = ProgressTimer::RADIALCW;
		if (pRet->initWithTrackSprite_ProgressTimer_ThumbSprite(backgroundSprite, progressTimer, thumbSprite))
		{
			pRet->autorelease();
		}
		else
		{
			CC_SAFE_DELETE(pRet);
		}
	}
	return pRet;
}