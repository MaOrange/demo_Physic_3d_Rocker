#include "AppDelegate.h"
#include "HelloWorldScene.h"

USING_NS_CC;

#include"GameHeader.h"

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::createWithRect("demo_Physic_3d_Rocker", Rect(0, 0, 1280, 720));
        director->setOpenGLView(glview);
    }

    director->getOpenGLView()->setDesignResolutionSize(1280, 720, ResolutionPolicy::SHOW_ALL);

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0f / 60);

    FileUtils::getInstance()->addSearchPath("res");

	FileUtils::getInstance()->addSearchPath("res/Life");

	FileUtils::getInstance()->addSearchPath("res/Audio");
	//user defalut:

	Config::setBGMVol(UserDefault::sharedUserDefault()->getFloatForKey(BGM_VOL_KEY,1.0f));

	Config::setEffectVol(UserDefault::sharedUserDefault()->getFloatForKey(EFFECT_VOL_KEY,1.0f));

	Config::setIsBGM(UserDefault::sharedUserDefault()->getBoolForKey(BGM_KEY,true));

	Config::setIsEffect(UserDefault::sharedUserDefault()->getBoolForKey(EFFECT_KEY,true));
	
	//audio
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(BGM_FIlE);
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(STD_HIT);
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(ADC_HIT);
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(ICYBLAST_HIT);
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(PLAINTATTACK_HIT);

	SimpleAudioEngine::getInstance()->playBackgroundMusic(BGM_FIlE,true);

    //HelloWorld
	/*auto scene = HelloWorld::createScene();
	director->runWithScene(scene);*/
	//
	//SceneManager::getInstance()->toHelloWorld();
	//SceneManager::getInstance()->toTitleScene();

	auto scene = TitleScene::createScene();

	director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();

	
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
