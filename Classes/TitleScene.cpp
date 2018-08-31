#include "TitleScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
USING_NS_CC;

TitleScene::TitleScene() {
    
}

Scene * TitleScene::createScene()
{
	auto scene = Scene::create();

	scene->addChild(create());

	return scene;
}

bool TitleScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	//CCLOG("%d", experimental::AudioEngine::play2d("Audio/bgmusic.wav"));

	auto rootNode = CSLoader::createNode("TitleScene.csb");

	this->addChild(rootNode);

	//retrieve
	_label_start = (ui::Text*)rootNode->getChildByName("Text_start");

	_label_start->addClickEventListener([=](Ref* psender) {SceneManager::getInstance()->toMainGame(); });

	_label_demo = (ui::Text*)rootNode->getChildByName("Text_demo");

	_label_demo->addClickEventListener([=](Ref* psender) {SceneManager::getInstance()->toHelloWorld(); });

	_label_config = (ui::Text*)rootNode->getChildByName("Text_config");

	_label_config->addClickEventListener([=](Ref* psender) 
	{
		auto config = Config::create();
		this->addChild(config);

		
		//config->setPosition(Point::ZERO);
	});

	auto infoButton = (ui::Button*)rootNode->getChildByName("Button_1");

	infoButton->addClickEventListener([&](Ref* psender) 
	{
		auto info = CSLoader::createNode("InfoScene.csb");

		this->addChild(info);

		auto backButton = (ui::Text*)info->getChildByName("Text_1");

		backButton->addClickEventListener([=](Ref* psender) 
		{
			info->removeFromParentAndCleanup(true);
		});
	});

	return true;
}

void TitleScene::onEnter()
{
	Layer::onEnter();
	
	
}

void TitleScene::onExit()
{
	//Director::getInstance()->getEventDispatcher()->removeAllEventListeners();

	Layer::onExit();
}
