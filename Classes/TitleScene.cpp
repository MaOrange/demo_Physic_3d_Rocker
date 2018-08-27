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

	//retri
	_label_start = (ui::Text*)rootNode->getChildByName("Text_start");

	//_label_start->addClickEventListener([=](Ref* psender) {SceneManager::getInstance()->toHelloWorld()});

	_label_demo = (ui::Text*)rootNode->getChildByName("Text_demo");

	_label_demo->addClickEventListener([=](Ref* psender) {SceneManager::getInstance()->toHelloWorld(); });

	_label_config = (ui::Text*)rootNode->getChildByName("Text_config");

	_label_config->addClickEventListener([=](Ref* psender) 
	{
		auto config = Config::create();
		this->addChild(config);

		
		//config->setPosition(Point::ZERO);
	});

	return true;
}

void TitleScene::onEnter()
{
	Layer::onEnter();
	
	
}
