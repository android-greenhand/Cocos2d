#include "LoginHistory.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
USING_NS_CC;

#include "HuffCode\HuffCode.h"
using namespace cocostudio::timeline;

Scene* LoginHistory::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = LoginHistory::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;

}

// on "init" you need to initialize your instance
bool LoginHistory::init()
{
    if ( !Layer::init() )
    {
        return false;
	}
	
	
	

	//界面背景
	auto s = Sprite::create("floor.jpg");
	s->setAnchorPoint(Vec2(0, 0));
	s->setScale(Director::getInstance()->getWinSize().width / s->getContentSize().width, Director::getInstance()->getWinSize().height / s->getContentSize().height);
	addChild(s);
	
	//返回游戏菜单
	auto m1 = MenuItemImage::create("back.png", "back.png", this, menu_selector(LoginHistory::ReturnMainSence));
	auto m = Menu::create(m1, 0);
	m->alignItemsVertically();
	m->setScale(0.05);
	m->setAnchorPoint(Vec2(0, 0));
	m->setPosition(870, 100);
	addChild(m);


	HuffCode huff;
	huff.Process();
	auto l = Label::create(huff.stxet, "cyes.ttf", 25);
	l->setAnchorPoint(Vec2(0, 0));
	l->setPosition(300, 400);
	

	//l->setLineBreakWithoutSpace(true);

	
	l->enableGlow(Color4B::YELLOW);
	
	addChild(l);
    return true;
}

void LoginHistory::ReturnMainSence(Ref*)
{
	Director::getInstance()->popScene();
}
