#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();

	//scene->getPhysicsWorld()->setGravity(Point::ZERO);
	scene->getPhysicsWorld()->setGravity(Vec2(0,0));

	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    /**  you can create scene with following comment code instead of using csb file.
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    **/
    
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    //auto rootNode = CSLoader::createNode("MainScene.csb");
	//auto rootNode = Sprite::create("HelloWorld.png");
	auto rootNode = Sprite::create("3D/map.jpg");

	//rootNode->setRotation3D(Vec3(-90,0,0));

	rootNode->setCameraMask(4);

	//add light
	auto light = AmbientLight::create(Color3B::WHITE);
	addChild(light);

	auto light2 = DirectionLight::create(Vec3(-1.0f, -2.0f, -2.0f), Color3B::GREEN);
	addChild(light2);

	

    this->addChild(rootNode,-1);
	auto hero = Sprite3D::create("3D/HeroAnimation.c3b");
	_hero = hero;

	auto testArr = hero->getMeshes();

	this->addChild(hero,2);

	hero->setCameraMask(2);

	hero->setPosition(200, 200);

	//hero->setScale(2);

	hero->setRotation3D(Vec3(0,0,0));

	hero->setGlobalZOrder(100);

	hero->setContentSize(Size(0.1f, 0.1f));

	//hero->runAction(RepeatForever::create(RotateBy::create(2,Vec3(0,90,0))));

	auto newAnimation = Animation3D::create("3D/HeroAnimation.c3b");

	auto newAnimate = Animate3D::create(newAnimation,0.0f,1.0f);

	hero->runAction(RepeatForever::create(newAnimate));

	//_camera_bg = Camera::createPerspective(60, size.width / size.height, 1.0, 10000);

	_camera_bg = Camera::createOrthographic(1.0f,1.0f, 1.0, 10000);

	//_camera_bg->setRotation3D(Vec3(-45, 0, 0));
	//_camera_bg->setRotation3D(Vec3(-90, 0, 0));

	//_camera_bg->setPosition3D(Vec3(0, 510, 230));
	_camera_bg->setPosition3D(Vec3(0, 0, 230));

	_camera_bg->setCameraFlag(CameraFlag::USER2);

	addChild(_camera_bg,1);

	//_camera_hero = Camera::createPerspective(60, size.width/size.height,1.0,10000);
	_camera_hero = Camera::createOrthographic(size.width, size.height, 0.0f, 10000);

	_camera_hero->setRotation3D(Vec3(45,0,0));

	//_camera_hero->setRotation3D(Vec3(-45,0,0));
	//_camera_hero->setRotation3D(Vec3(-90, 0, 0));

	//_camera_hero->setPosition3D(Vec3(0, 510,230));
	_camera_hero->setPosition3D(Vec3(0, -0.1f, 0.1f));

	_camera_hero->setCameraFlag(CameraFlag::USER1);

	addChild(_camera_hero,2);


	
	//
	/*auto Sp = Sprite3D::create("AnimationTest.c3b");

	this->addChild(Sp);

	Sp->setScale(7);

	Sp->setTexture("123.png");

	Sp->setRotation3D(Vec3(0,45,0));

	Sp -> setPosition(size.width / 2, size.height / 2);

	auto An = Animation3D::create("AnimationTest.c3b");

	auto animate = Animate3D::create(An,0.0f,5.0f);

	auto animateForever = RepeatForever::create(animate);

	Sp->runAction(animateForever);

	Sp->runAction(RepeatForever::create( RotateBy::create(3, Vec3(90, 90, 90))));*/

	//listener
	EventListenerKeyboard* listener = EventListenerKeyboard::create();

	listener->onKeyPressed = CC_CALLBACK_2(HelloWorld::keyboardCallBack,this);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	//physics editor/////////////////////////////
	_cache = PhysicsShapeCache::getInstance();

	_cache->addShapesWithFile("PhysicsEditor/stdCollider.plist");

	//hero->setPhysicsBody(_cache->createBodyWithName("heroCut"));
	hero->setPhysicsBody(PhysicsBody::createCircle(15));

	hero->getPhysicsBody()->getShapes().at(0)->setRestitution(0);//re

	//hero->getPhysicsBody()->setVelocity(Vec2(100,100));

	

	//hero->getPhysicsBody()->setPositionOffset(Vec2(-55.5058441,-16.5153732));
	
	

	//box///////////////////////////
	auto box = PhysicsBody::createEdgeBox(size, PHYSICSBODY_MATERIAL_DEFAULT, 5.0f);

	auto edgeNode = Node::create();

	edgeNode->setPosition(size.width / 2, size.height / 2);

	edgeNode->setPhysicsBody(box);

	this->addChild(edgeNode);

	_box = edgeNode;

	box->setCategoryBitmask(0x01);

	box->setCollisionBitmask(0x01);

	box->setContactTestBitmask(0x01);

	_hero->getPhysicsBody()->setCategoryBitmask(0x01);

	_hero->getPhysicsBody()->setCollisionBitmask(0x01);

	_hero->getPhysicsBody()->setContactTestBitmask(0x01);


	//test Sprite
	auto testSp = Sprite::create("RockerResources/SkillIcon.png");

	testSp->setPhysicsBody(PhysicsBody::createCircle(50));

	testSp->setPosition(200,200);

	//this->addChild(testSp);

	//rocker///////////////////////////////////////////

	_rocker = Rocker::createWith("","");

	_rocker->setPosition(Vec2(size.width*0.2,size.height*0.2));

	this->addChild(_rocker,10);

	_rocker->setScale(1.5);

	_rocker->rockerOnChange = [=](Vec2 & vec) 
	{
		v = 2*vec;//update velocity

		///////////////////////////////////////
		//Vec2 tempV = vec;

		/*if (_contect)
		{
			auto data = _contect->getContactData();

			Vec2 normal = data->normal / data->normal.length();

			float product = (tempV.x * normal.x + tempV.y * normal.y);

			if (product>0)
			{
				tempV = tempV - product*(normal);
			}

		}

		_hero->getPhysicsBody()->setVelocity(tempV);*/


		if (vec.x != 0 && vec.y != 0)
		{
			this->_hero->setRotation(-CC_RADIANS_TO_DEGREES(vec.getAngle()) + 90);
		}
	};

	//////////////////////////////////////////////////

	/////setMaterial////////////
	PhysicsMaterial GAME_MATERIAL;
	GAME_MATERIAL.friction = 0.0f;
	GAME_MATERIAL.restitution = 0.0f;

	_hero->getPhysicsBody()->getShapes().at(0)->setMaterial(GAME_MATERIAL);

	testSp->getPhysicsBody()->getShapes().at(0)->setMaterial(GAME_MATERIAL);

    return true;
}

void HelloWorld::keyboardCallBack(EventKeyboard::KeyCode keyCode, Event * event)
{
	Vec3 tempVec,tempRotation=Vec3(0,0,0);
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_A:
		tempVec= Vec3(-10,0,0);
		break;
	case EventKeyboard::KeyCode::KEY_S:
		tempVec=Vec3(0, -10, 0);
		break;

	case EventKeyboard::KeyCode::KEY_D:
		tempVec=Vec3(+10, 0, 0);
		break;

	case EventKeyboard::KeyCode::KEY_W:
		tempVec=Vec3(0, +10, 0);
		break;
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		tempVec=Vec3(0, 0, +10);
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		tempVec=Vec3(0, 0, -10);
		break;

	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		tempRotation= Vec3(0,0,+10);
		break;

	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		tempRotation = Vec3(0, 0, -10);
		break;

	case EventKeyboard::KeyCode::KEY_1:
		tempRotation = Vec3(0,+10,0);
		break;
	case EventKeyboard::KeyCode::KEY_2:
		tempRotation = Vec3(0, -10, 0);
		break;
	default:
		break;
	}
	//_camera_hero->setPosition3D(_camera_hero->getPosition3D()+tempVec);

	//_camera_bg->setPosition3D(_camera_bg->getPosition3D() + tempVec);

	//_hero->setPosition3D(_hero->getPosition3D()+tempVec);

	//_camera_hero->setRotation3D(_camera_hero->getRotation3D()+tempRotation);

	//_cache->setBodyOnSprite()

	_hero->setPosition3D(_hero->getPosition3D()+tempVec);

	_hero->setRotation3D(_hero->getRotation3D()+tempRotation);

	//_camera_bg->setRotation3D(_camera_bg->getRotation3D() + tempRotation);

	//auto position = _camera_hero->getPosition3D();
	//CCLOG("Position:(%f,%f,%f)",position.x,position.y,position.z);

	auto rotation = _hero->getRotation3D();
	CCLOG("Rotation:(%f,%f,%f)", rotation.x, rotation.y, rotation.z);
}

void HelloWorld::onEnter()
{
	Layer::onEnter();

	this->scheduleUpdate();

	EventListenerPhysicsContactWithBodies* contactListener=EventListenerPhysicsContactWithBodies::create(_hero->getPhysicsBody(),_box->getPhysicsBody());

	contactListener->onContactBegin = [=](PhysicsContact& contact)->bool 
	{
		_contect = &contact;

		return true;
	};

	contactListener->onContactPreSolve = [=](PhysicsContact& contact, PhysicsContactPreSolve& solve)->bool
	{
		_contect = &contact;

		return true;//////save cpu overhead or prepare for cases????
	};

	contactListener->onContactSeparate = [=](PhysicsContact& contact) 
	{
		_contect = nullptr;
	};

	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(contactListener, 1);
}

void HelloWorld::onExit()
{
	Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
}

void HelloWorld::update(float dt)
{
	if (_contect)
	{
		auto data = _contect->getContactData();

		Vec2 normal = data->normal / data->normal.length();

		float product = (v.x * normal.x + v.y * normal.y);

		if (product > 0)
		{
			v = v - product*(normal);
		}

	}

	//Layer::update(dt);
	//tunnel bug fix
	for (int i=1;i<=3;i++)
	{
		_hero->setPosition(_hero->getPosition() + v*dt/3);
	}

	//_hero->getPhysicsBody()->setVelocity(v);
}




