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

	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	//tunnel bug fix
	scene->getPhysicsWorld()->setAutoStep(true);
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

	layer->_scene = scene;

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
	//Layers
	_field = Layer::create();

	_uiLayer = Layer::create();

	_bg = Layer::create();

	this->addChild(_field,2);

	this->addChild(_uiLayer, 3);

	this->addChild(_bg,1);

	_field->setCameraMask(2);

	_bg->setCameraMask(2);

    //auto rootNode = CSLoader::createNode("MainScene.csb");
	//auto rootNode = Sprite::create("HelloWorld.png");
	auto rootNode = Sprite::create("3D/map.jpg");

	rootNode->setPosition(size.width/2,size.height/2);

	rootNode->setScale(2.0,4.0);

	//rootNode->setRotation3D(Vec3(-90,0,0));

	rootNode->setCameraMask(2);

	//add light
	auto light = AmbientLight::create(Color3B::WHITE);
	addChild(light);

	auto light2 = DirectionLight::create(Vec3(-1.0f, -2.0f, -2.0f), Color3B::WHITE);
	addChild(light2);

    _bg->addChild(rootNode,-100);

	rootNode->setGlobalZOrder(-100);

	auto hero = Sprite3D::create("3D/HeroAnimation.c3b");
	_hero = hero;

	auto testArr = hero->getMeshes();

	_field->addChild(hero,2);

	hero->setCameraMask(2);

	hero->setPosition(500, 500);

	hero->setPositionZ(0);

	//hero->setScale(2);

	hero->setRotation3D(Vec3(0,0,0));

	hero->setContentSize(Size(0.1f, 0.1f));

	//hero->runAction(RepeatForever::create(RotateBy::create(2,Vec3(0,90,0))));

	auto newAnimation = Animation3D::create("3D/HeroAnimation.c3b");

	auto newAnimate = Animate3D::create(newAnimation,0.0f,1.0f);

	hero->runAction(RepeatForever::create(newAnimate));

	hero->setTag(1);

	//_camera_bg = Camera::createPerspective(60, size.width / size.height, 1.0, 10000);

	_camera_bg = Camera::createOrthographic(1.0f,1.0f, 0.1f, 10000);

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
	_camera_hero->setPosition3D(Vec3(0, -50.0f, 50.0f));

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

	auto edgeNode = Wall::create();

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

	auto wallSprite = Wall::create();

	auto testSp = Sprite::create("RockerResources/skillDisabled.png");

	testSp->setPhysicsBody(PhysicsBody::createCircle(80));

	wallSprite->setPosition(500,500);

	testSp->getPhysicsBody()->setCategoryBitmask(0x01);

	testSp->getPhysicsBody()->setCollisionBitmask(0x01);

	testSp->getPhysicsBody()->setContactTestBitmask(0x01);

	testSp->setCameraMask(2);

	testSp->setGlobalZOrder(-100);

	wallSprite->addChild(testSp);

	_field->addChild(wallSprite);

	//rocker///////////////////////////////////////////

	_rocker = Rocker::createWith("","");

	_rocker->setPosition(Vec2(size.width*0.2,size.height*0.3));

	_uiLayer->addChild(_rocker,10);

	_rocker->setScale(2.0);

	_rocker->rockerOnChange = [=](Vec2 & vec) 
	{
		v = 3*vec;//update velocity

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
	GAME_MATERIAL.restitution = 1000.0f;

	testSp->getPhysicsBody()->setDynamic(false);

	_hero->getPhysicsBody()->getShapes().at(0)->setMaterial(GAME_MATERIAL);

	testSp->getPhysicsBody()->getShapes().at(0)->setMaterial(GAME_MATERIAL);

	//group
	testSp->getPhysicsBody()->setGroup(1);

	_box->getPhysicsBody()->setGroup(1);

	_hero->getPhysicsBody()->setGroup(1);

	//test Entity/////////////////////////////////
	auto heroEntity = Entity::createWith("3D/HeroAnimation.c3b");

	heroEntity->setPosition(Vec2(500,500));

	heroEntity->setCollideGroup(1);

	heroEntity->setPhysicsBody(PhysicsBody::createCircle(15));

	heroEntity->getPhysicsBody()->setGroup(1);

	_heroEntity = heroEntity;

	auto body = heroEntity->getPhysicsBody();

	body->setCollisionBitmask(0x00000001);

	body->setContactTestBitmask(0x00000003);

	body->setCategoryBitmask(0x00000001);

	body->setResting(false);

	heroEntity->getSprite3D()->setCameraMask(2);

	heroEntity->getLifeBar()->setCameraMask(2);

	//heroEntity->getLifeBar()->setCameraMask();

	auto heroController = HeroController::create();

	heroController->setEntityControlled(heroEntity);

	heroController->setRocker(_rocker);

	heroEntity->setController(heroController);

	_field->addChild(heroEntity);
	//////////////////////////////////////////////


	//////////test LifeBar
	auto lifeBar = LifePlus::creatWithMaxLife(100.0f,"Life/LifePlus.csb");

	lifeBar->setPosition(Vec2(100,100));

	lifeBar->setCameraMask(2);

	lifeBar->setGlobalZOrder(100);

	//this->addChild(lifeBar,10);
	///////////////////

	//test Crab///////////////
	auto crabEntity = Entity::createWith("3D/EnemyAnimation.c3b");

	crabEntity->setPosition(Vec2(70, 70));

	crabEntity->setCollideGroup(1);

	crabEntity->setPhysicsBody(PhysicsBody::createCircle(15));

	crabEntity->getPhysicsBody()->setGroup(1);

	crabEntity->setCameraMask(2);

	auto crabBody = crabEntity->getPhysicsBody();

	crabBody->setContactTestBitmask(0x03);

	crabBody->setCategoryBitmask(0x01);

	auto crabController = EnemyController_Crab::create();

	crabEntity->setController(crabController);

	crabController->setEntityControlled(crabEntity);

	_field->addChild(crabEntity);

	///////////////////////////////////////////////////

	///test SkillRocket
	auto PAskill = Skill_PlainAttack::create();

	PAskill->setEntityController(heroController);

	_uiLayer->addChild(PAskill->getSkillRocker());

	PAskill->getSkillRocker()->setPosition(size.width*0.85,size.height*0.23);

	/////////
	//test STD enemy//////////////////////////////
	auto stdEntity = Entity::createWith("3D/EnemyAnimation.c3b");

	stdEntity->setPosition(Vec2(340, 340));

	stdEntity->setCollideGroup(1);

	stdEntity->setPhysicsBody(PhysicsBody::createCircle(15));

	stdEntity->getPhysicsBody()->setGroup(1);

	stdEntity->setCameraMask(2);

	auto stdBody = stdEntity->getPhysicsBody();

	stdBody->setContactTestBitmask(0x03);

	stdBody->setCategoryBitmask(0x01);

	auto stdController = EnemyController_STD::create();

	stdEntity->setController(stdController);

	stdController->setEntityControlled(stdEntity);

	stdController->setAttackTarget(heroEntity);

	_field->addChild(stdEntity);

	//test icyBlast//////////////
	auto IBSkill = Skill_IcyBlast::create();

	IBSkill->setEntityController(heroController);

	_uiLayer->addChild(IBSkill->getSkillRocker());

	IBSkill->getSkillRocker()->setPosition(Vec2(size.width*0.85f,size.height*0.5f));

	//set skill cancel
	if (auto cancel=SkillRocker::_cancel)
	{
		cancel->removeFromParent();

		_uiLayer->addChild(cancel);

		SkillRocker::_cancel->setPosition(size.width*0.85, size.height*0.86);
	}

	//test IcyBlock.h
	auto IBKSkill = Skill_IcyBlock::create();

	IBKSkill->setEntityController(heroController);

	_uiLayer->addChild(IBKSkill->getSkillRocker());

	IBKSkill->getSkillRocker()->setPosition(Vec2(size.width*0.72f, size.height*0.4f));
	
	/////////////////////////

	//test Skill_Flash.h
	auto falshSkill = Skill_Flash::create();

	falshSkill->setEntityController(heroController);

	_uiLayer->addChild(falshSkill->getSkillRocker());

	falshSkill->getSkillRocker()->setPosition(Vec2(size.width*0.65,size.height*0.20));

	///////////////////////

	//ScoreBoard.h////////////
	auto score = ScoreBoard::create();

	_uiLayer->addChild(score,3);

	score->setPosition(Vec2(size.width/2,size.height*0.88));

	score->addScore(100);

	_score = score;

	_soulFire = ParticleSystemQuad::create("Particle/soulFire.plist");

	_soulFire->setPosition(Vec2(size.width *0.42, size.height*0.88));

	_soulFire->setScale(0.8f);

	_uiLayer->addChild(_soulFire);
	////////////////////////

	//EnemyController_ADC.h///////
	auto adcEntity = Entity::createWith("3D/EnemyAnimation.c3b");

	adcEntity->setPosition(Vec2(600, 600));

	adcEntity->setCollideGroup(1);

	adcEntity->setPhysicsBody(PhysicsBody::createCircle(15));

	adcEntity->getPhysicsBody()->setGroup(1);

	adcEntity->setCameraMask(2);

	auto adcBody = adcEntity->getPhysicsBody();

	adcBody->setContactTestBitmask(0x03);

	adcBody->setCategoryBitmask(0x01);

	auto adcController = EnemyController_ADC::create();

	adcEntity->setController(adcController);

	adcController->setEntityControlled(adcEntity);

	adcController->setAttackTarget(heroEntity);

	_field->addChild(adcEntity);

	///////////////////////////////
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
		tempRotation=Vec3(10, 0, 0);
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		tempRotation=Vec3(-10, 0, 0);
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

	case EventKeyboard::KeyCode::KEY_Z:
		_heroEntity->getLifeBar()->recover(10);
		break;
	case EventKeyboard::KeyCode::KEY_X:
		_heroEntity->getLifeBar()->damage(15);
		break;
	default:
		break;
	}
	//_camera_hero->setPosition3D(_camera_hero->getPosition3D()+tempVec);

	//_camera_bg->setPosition3D(_camera_bg->getPosition3D() + tempVec);

	//_hero->setPosition3D(_hero->getPosition3D()+tempVec);

	_camera_hero->setRotation3D(_camera_hero->getRotation3D()+tempRotation);

	//_cache->setBodyOnSprite()

	//_hero->setPosition3D(_hero->getPosition3D()+tempVec);

	//_hero->setRotation3D(_hero->getRotation3D()+tempRotation);

	//_camera_bg->setRotation3D(_camera_bg->getRotation3D() + tempRotation);

	//auto position = _camera_hero->getPosition3D();
	//CCLOG("Position:(%f,%f,%f)",position.x,position.y,position.z);

	auto rotation = _hero->getRotation3D();
	CCLOG("Rotation:(%f,%f,%f)", rotation.x, rotation.y, rotation.z);
}

void HelloWorld::onEnter()
{
	Layer::onEnter();

	_dieListener = EventListenerCustom::create("EntityDie",
		[=](EventCustom* event) {
		Entity* entity= reinterpret_cast<Entity*>(event->getUserData());

		if (entity)
		{
			CCLOG("Die");
			delayCall( 
			CC_CALLBACK_0(HelloWorld::enemyDie,this,entity)
			, 1.5f);
			delayCall(CC_CALLBACK_0(HelloWorld::addEnemySTD,this), 5.0f);
			//scheduleOnce(schedule_selector(HelloWorld::addEnemySTD) ,5.0f);
		}

	}
		);

	_dispatcher->addEventListenerWithSceneGraphPriority(_dieListener,this);

	this->scheduleUpdate();

	EventListenerPhysicsContactWithBodies* contactListener=EventListenerPhysicsContactWithBodies::create(_hero->getPhysicsBody(),_box->getPhysicsBody());

	EventListenerPhysicsContactWithGroup* newListener = EventListenerPhysicsContactWithGroup::create(1);

	//EventListenerPhysicsContactWithShapes::create

	newListener->onContactBegin=contactListener->onContactBegin = [=](PhysicsContact& contact)->bool 
	{
		_contect = &contact;

		_contacts.pushBack(&contact);

		return true;
	};

	newListener->onContactPreSolve= contactListener->onContactPreSolve = [=](PhysicsContact& contact, PhysicsContactPreSolve& solve)->bool
	{
		_contect = &contact;

		return true;//////save cpu overhead or prepare for cases????
	};

	newListener->onContactSeparate=contactListener->onContactSeparate = [=](PhysicsContact& contact) 
	{
		_contacts.eraseObject(&contact);
		_contect = nullptr;
	};

	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(contactListener, 1);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(newListener, 1);
}

void HelloWorld::onExit()
{
	Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
	Layer::onExit();
}

void HelloWorld::update(float dt)
{
	
	//Layer::update(dt);
	//tunnel bug fix

	
	cameraUpdate();
}

void HelloWorld::addEnemySTD()
{
	auto stdEntity = Entity::createWith("3D/EnemyAnimation.c3b");

	stdEntity->setPosition(Vec2(340, 340));

	stdEntity->setCollideGroup(1);

	stdEntity->setPhysicsBody(PhysicsBody::createCircle(15));

	stdEntity->getPhysicsBody()->setGroup(1);

	stdEntity->setCameraMask(2);

	auto stdBody = stdEntity->getPhysicsBody();

	stdBody->setContactTestBitmask(0x03);

	stdBody->setCollisionBitmask(0x03);

	stdBody->setCategoryBitmask(0x01);

	auto stdController = EnemyController_STD::create();

	stdEntity->setController(stdController);

	stdController->setEntityControlled(stdEntity);

	stdController->setAttackTarget(_heroEntity);

	_field->addChild(stdEntity);
}



void HelloWorld::delayCall(const std::function<void()>& callback, float delay)
{
	auto call = CallFunc::create(callback);

	auto Timedelay = DelayTime::create(delay);

	auto combo = Sequence::create(Timedelay,call,NULL);

	this->runAction(combo);
}

void HelloWorld::cameraUpdate()
{
	_camera_hero->setPosition(_heroEntity->getPosition()-Vec2(size.width/2,size.height/sqrt(2)));
}

void HelloWorld::enemyDie(Entity * enemy)
{
	auto soul = ParticleSystemQuad::create("Particle/soul.plist");

	//soul->setCameraMask(enemy->getSprite3D()->getCameraMask());

	soul->setPosition(convertToPosInCamera(enemy->getPosition()));

	_uiLayer->addChild(soul);

	enemy->removeFromParentAndCleanup(true);

	auto flyTo = MoveTo::create(0.5f,_soulFire->getPosition());

	auto add = CallFunc::create([=]() 
	{
		_score->addScore(300);

		changeColor();
	});

	auto wait2 = DelayTime::create(0.2f);

	auto stop = CallFunc::create([=]() {soul->stopSystem(); });

	auto wait3 = DelayTime::create(3.0f);

	auto des = CallFunc::create([=]() {soul->removeFromParentAndCleanup(true);});

	auto combo = Sequence::create(flyTo,add, wait2,stop,wait3,des,NULL);

	soul->runAction(combo);
}

Vec2 HelloWorld::convertToPosInCamera(const Vec2 & vec)
{
	auto temp = vec-_camera_hero->getPosition();

	return Vec2(temp.x,temp.y/sqrt(2));
}

void HelloWorld::changeColor()
{
	auto tempC = _soulFire->getStartColor();

	switch (_colorState)
	{
	case 1:
		if (tempC.b>=_colorRate)
		{
			tempC.b -= _colorRate;
			break;
		}
		else
		{
			_colorState = 2;
		}
		
	case 2:
		if (tempC.b<=255-_colorRate)
		{
			tempC.b += _colorRate;
			break;
		}
		else
		{
			_colorState = 3;
		}
	case 3:
		if (tempC.r >= _colorRate)
		{
			tempC.r -= _colorRate;
			break;
		}
		else
		{
			_colorState = 4;
		}
	case 4:
		if (tempC.r <= 255 - _colorRate)
		{
			tempC.r += _colorRate;
			break;
		}
		else
		{
			_colorState = 1;
		}
	default:
		break;
	}

	_soulFire->setStartColor(tempC);

	_soulFire->setEndColor(tempC);
}






