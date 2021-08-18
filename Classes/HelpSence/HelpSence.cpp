#include "HelpSence.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
USING_NS_CC;

using namespace cocostudio::timeline;

Scene* HelpSence::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = HelpSence::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;

}

// on "init" you need to initialize your instance
bool HelpSence::init()
{
    if ( !Layer::init() )
    {
        return false;
	}
	
	//音效
	

	//帮助界面背景
	auto s = Sprite::create("floor.jpg");
	s->setAnchorPoint(Vec2(0, 0));
	s->setScale(Director::getInstance()->getWinSize().width / s->getContentSize().width, Director::getInstance()->getWinSize().height / s->getContentSize().height);
	addChild(s);
	
	//返回游戏菜单
	auto m1 = MenuItemImage::create("back.png", "back.png", this, menu_selector(HelpSence::ReturnMainSence));
	auto m = Menu::create(m1, 0);
	m->alignItemsVertically();
	m->setScale(0.05);
	m->setAnchorPoint(Vec2(0, 0));
	m->setPosition(870, 100);
	addChild(m);

	//象棋口诀
	auto dic = Dictionary::createWithContentsOfFile("CHN_Strings.xml");
	auto s1 = (String *)dic->objectForKey("string6");
	auto l1 = Label::create(s1->getCString(), "cyes.ttf", 30);
	l1->setAnchorPoint(Vec2(0, 0));
	l1->setPosition(280, 200);
	addChild(l1);

	
    return true;
}

void HelpSence::ReturnMainSence(Ref*)
{
	Director::getInstance()->popScene();
}
