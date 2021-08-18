#include "MainInterface.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include"HelpSence\HelpSence.h"
#include"SelectStone\SelectStone.h"
#include "ChessBoard.h"
#include "LoginHistory\LoginHistory.h"
USING_NS_CC;
#include"SimpleAudioEngine.h"
using namespace cocostudio::timeline;
using namespace CocosDenshion;
Scene* MainInterface::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = MainInterface::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainInterface::init()
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
 
	auto s = Sprite::create("mainsencese.png");
	s->setAnchorPoint(Vec2(0, 0));
	s->setScale(Director::getInstance()->getWinSize().width / s->getContentSize().width, Director::getInstance()->getWinSize().height / s->getContentSize().height);
	addChild(s);



	
	SimpleAudioEngine::getInstance()->playBackgroundMusic("1.mp3");
	auto sm = Sprite::create("playmusic.png");
	auto sm1 = Sprite::create("pausemusic.png");
	sm->setPosition(930, 610);
	sm1->setPosition(930, 610);
	sm->setScale(0.1);
	sm1->setScale(0.1);
	auto e1 = EventListenerTouchOneByOne::create();
	static int k = 1;
	e1->setSwallowTouches(true);
	e1->onTouchBegan = [=](Touch *t, Event *e){
		if (sm->getBoundingBox().containsPoint(t->getLocation()) && k){
			sm1->setZOrder(0);
			sm1->setZOrder(1);
			SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
			k = 0;
			return true;
		}
		if (sm1->getBoundingBox().containsPoint(t->getLocation()) && !k){
			sm->setZOrder(0);
			sm->setZOrder(1);
			SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
			k = 1;
			return true;
		}
		return false;
	};
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(e1, sm);
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(e1->clone(), sm1);




	//人机 dan开始 帮助 游戏菜单
	
	auto m1 = MenuItemImage::create("SingleMachine.png", "SingleMachine.png", this, menu_selector(MainInterface::EnterSingleMachineScene));
	auto m2 = MenuItemImage::create("Single.png", "Single.png", this, menu_selector(MainInterface::EnterSingleStartScene));
	auto m3 = MenuItemImage::create("Double.png", "Double.png", this, menu_selector(MainInterface::EnterDoubleStartScene));
	auto m4 = MenuItemImage::create("Help.png", "Help.png", this, menu_selector(MainInterface::EnterHelpScene));
	auto m5 = MenuItemImage::create("Quit.png", "Quit.png", this, menu_selector(MainInterface::Quit));
	
	m1->setScale(0.333,0.332);
	m2->setScale(0.08);
	m3->setScale(0.08);
	m4->setScale(0.08);
	m5->setScale(0.08);
	auto m = Menu::create(m1, m2, m3,m4,m5,0);
	m->setPosition(630, 260);
	m->alignItemsVertically();
	m->setScale(0.9);
	addChild(m);
	//音效
	addChild(sm1);
	addChild(sm);
	
	
	

	// 登陆历史记录查看
	auto mhistory = MenuItemImage::create("loginhistory.png", "loginhistory.png", this, menu_selector(MainInterface::EnterLoginHistory));
	mhistory->setScale(0.126);
	auto mhs = Menu::create(mhistory,0);
	mhs->setPosition(880, 610);
	addChild(mhs);
	return true;
}
void MainInterface::EnterSingleMachineScene(Ref*)
{
	ChessBoard::isSingleMachine = true;
	auto s = ChessBoard::createScene();
	Director::getInstance()->pushScene(TransitionSplitRows::create(1.2f, s));
	return;
}
void MainInterface::EnterSingleStartScene(Ref*)
{
	ChessBoard::isdouble = false;
	auto s = SelectStone::createScene();
	Director::getInstance()->pushScene(TransitionSplitRows::create(1.2f, s));
	return;
}
void MainInterface::EnterDoubleStartScene(Ref*)
{
	MsgisDouble *msg = new MsgisDouble;
	Clientclass::GetInstance()->SendData((char*)msg);

	ChessBoard::isdouble = true;
	auto s = SelectStone::createScene();
	Director::getInstance()->pushScene(TransitionSplitRows::create(1.2f, s));



	return;
}
void MainInterface::EnterHelpScene(Ref*)
{
	auto s = HelpSence::createScene();
	Director::getInstance()->pushScene(TransitionPageTurn::create(1.2f, s, true));
	return;
}
void MainInterface::EnterLoginHistory(Ref*)
{
	auto s = LoginHistory::createScene();
	Director::getInstance()->pushScene(TransitionPageTurn::create(1.2f, s, true));
	return;
}
void MainInterface::Quit(Ref*)
{
	Director::getInstance()->end();
}
