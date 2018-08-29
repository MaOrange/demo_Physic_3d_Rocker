#pragma execution_character_set("utf-8")


#include "GameOver.h"


GameOver::GameOver() {
    
}

GameOver * GameOver::createWithScore(int score)
{
	auto newLayer = create();

	newLayer->initWithScore(score);

	return newLayer;
}


bool GameOver::initWithScore(int score)
{
	auto rootNode = CSLoader::createNode("EndScene.csb");

	this->addChild(rootNode);

	auto panel = (Layout*)rootNode->getChildByName("Panel_1");

	Size size = panel->getContentSize();

	Text* _tBack = (Text*)panel->getChildByName("Text_back");

	//tBack
	_tBack->addClickEventListener([=](Ref* psender) {SceneManager::getInstance()->toTitleScene(); });

	int highScore = UserDefault::getInstance()->getIntegerForKey(HIGH_SCORE_KEY, 0);

	if (score>highScore)
	{
		Text* _tTitle = (Text*)panel->getChildByName("Text_yourScore");
		_tTitle->setString("新纪录!");
		UserDefault::getInstance()->setIntegerForKey(HIGH_SCORE_KEY,score);
	}
	else
	{
		auto highScoreLabel = Label::createWithTTF(String::createWithFormat("最高分%d",highScore)->getCString(),"Fonts/title.ttf",40);
		highScoreLabel->setPosition(Vec2(size.width/2,size.height*0.35));
		panel->addChild(highScoreLabel,10);
	}

	auto scoreBoard= ScoreBoard::createWithLabel(Label::createWithTTF("","Fonts/title.ttf",200));

	scoreBoard->getScoreLabel()->setColor(Color3B::YELLOW);

	scoreBoard->setTitle("");

	scoreBoard->setScore(0);

	scoreBoard->addScore(score);

	scoreBoard->setPosition(Vec2(size.width/2,size.height/2));

	//scoreBoard->setTitle("得分");

	scoreBoard->setUpdateSpeed(score/0.4);

	panel->addChild(scoreBoard);

	//blocker
	auto newNode = Node::create();

	this->addChild(newNode, -100);

	auto newListener = EventListenerTouchOneByOne::create();

	newListener->onTouchBegan = [](Touch* touch, Event* event)->bool {return true; };

	newListener->setSwallowTouches(true);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(newListener,newNode);

	//animation
	cocostudio::timeline::ActionTimeline* action = CSLoader::createTimeline("EndScene.csb");

	this->runAction(action);

	action->gotoFrameAndPlay(action->getStartFrame(),false);

	return true;
}
