#include "Login.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Client\Clientclass.h"
USING_NS_CC;
using namespace cocostudio::timeline;

Scene* Login::createScene()
{
    auto scene = Scene::create();
	auto layer = Login::create();
    scene->addChild(layer);
    return scene;
}
bool Login::init()
{
    if ( !Layer::init() )
    {
        return false;
	}
	//µÇÂ½±³¾°
	auto s = Sprite::create("loginback.png");
	s->setAnchorPoint(Vec2(0, 0));
	s->setScale(Director::getInstance()->getWinSize().width / s->getContentSize().width, Director::getInstance()->getWinSize().height / s->getContentSize().height);
	addChild(s);
	//
	auto s2 = Sprite::create("editbix.png");
	auto s3= Sprite::create("editbix.png");
	s2->setAnchorPoint(Vec2(0, 0));
	s3->setAnchorPoint(Vec2(0, 0));
	s2->setScale(0.32);
	s3->setScale(0.32);
	s2->setPosition(420, 370);
	s3->setPosition(420, 270);
	addChild(s2);
	addChild(s3);
	//
	auto name = cocos2d::CCTextFieldTTF::textFieldWithPlaceHolder("UserName", "", 20);
	auto pw = cocos2d::CCTextFieldTTF::textFieldWithPlaceHolder("PassWord", "", 20);
	name->setPosition(470, 390);
	pw->setPosition(470, 290);
	addChild(name);
	addChild(pw);
	name->setDelegate(this);
	pw->setDelegate(this);
	name->setTag(1);
	pw->setTag(2);
	
	//ÓëÊäÈë°ó¶¨
	auto listener = EventListenerTouchOneByOne::create();   
	listener->onTouchBegan = [=](Touch *t, Event *e){
		if (name->getBoundingBox().containsPoint(t->getLocation()))
		{
			name->attachWithIME();
		}
		if (pw->getBoundingBox().containsPoint(t->getLocation()))
		{
			pw->attachWithIME();
		}
		return true;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,name);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener->clone(), pw);
	//	
	//µÇÂ½ ×¢²áÓÎÏ·²Ëµ¥
	auto m1 = MenuItemImage::create("Login.png", "Login.png", this, menu_selector(Login::MenuSendLogin));
	auto m2 = MenuItemImage::create("register.png", "register.png", this, menu_selector(Login::MenuSendLogin));
	auto m = Menu::create(m2,m1,0);
	m->alignItemsHorizontally();
	m->setScale(0.24);
	m->setAnchorPoint(Vec2(0, 0));
	m->setPosition(500, 200);
	addChild(m);
	//ÍË³ö
	auto m3 = MenuItemImage::create("Quit.png", "Quit.png", this, menu_selector(Login::Quit));
	auto mquit = Menu::create(m3, 0);
	mquit->alignItemsVertically();
	mquit->setScale(0.05);
	mquit->setAnchorPoint(Vec2(0, 0));
	mquit->setPosition(870, 100);
	addChild(mquit);

	schedule(schedule_selector(Login::EnterMainInterface),1);
    return true;
}

void Login::MenuSendLogin(Ref*)
{
	Clientclass::GetInstance()->SendData((char*)&msglogin);
}
void Login::Quit(Ref*)
{
	Director::getInstance()->end();
}

void Login::EnterMainInterface(float)
{
	cocos2d::CCTextFieldTTF *name = (CCTextFieldTTF *)getChildByTag(1);
	cocos2d::CCTextFieldTTF *pw = (CCTextFieldTTF *)getChildByTag(2);
	msglogin.SetUserName(name->getString().c_str());
	msglogin.SetUserPassword(pw->getString().c_str());
	if (Clientclass::GetInstance()->mloginreplay)
	{
		auto mchessboard = MainInterface::createScene();
		Director::getInstance()->replaceScene(TransitionSplitRows::create(1, mchessboard));
	}
}
