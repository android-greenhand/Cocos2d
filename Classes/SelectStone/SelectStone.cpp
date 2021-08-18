#include "SelectStone.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
#include"ChessBoard.h"
using namespace cocostudio::timeline;
SelectStone::SelectStone()
{
	m_time = 0;
	mflag = -1;
}
Scene* SelectStone::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = SelectStone::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SelectStone::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
	init_desk();
	Clientclass::GetInstance()->m_SelectStone = this;
    return true;
}

void SelectStone::init_desk()
{
	auto s = Sprite::create("floor.jpg"); 
	s->setAnchorPoint(Vec2(0, 0));
	s->setScale(Director::getInstance()->getWinSize().width / s->getContentSize().width, Director::getInstance()->getWinSize().height / s->getContentSize().height);
	addChild(s);

	

	//Í·Ïñ
	auto s2 = Sprite::create("tou.png");
	auto s3 = Sprite::create("tou1.png");
	s2->setPosition(400, 350);
	s3->setPosition(550, 350);
	addChild(s2);
	addChild(s3);

	auto m1 = MenuItemImage::create("bkg1.png", "bkg1.png", this, menu_selector(SelectStone::BlackStone));
	auto m2 = MenuItemImage::create("bkg2.png", "bkg2.png", this, menu_selector(SelectStone::RedStone));
	auto m = Menu::create(m1,m2,0);
	m->alignItemsHorizontallyWithPadding(100);
	m->setPosition(470, 250);
	addChild(m);

	//Ñ¡¿ò
	/*auto s4 = Sprite::create("selected.png");
	auto s5 = Sprite::create("selected.png");
	s4->setScale(90.0 / 56, 68.0 / 56);
	s5->setScale(90.0 / 56, 68.0 / 56);
	s4->setPosition(90, 500);
	s5->setPosition(870, 500);
	s4->setVisible(false);
	s5->setVisible(false);
	s4->setTag(1);
	s5->setTag(2);
	addChild(s4);
	addChild(s5);*/
	
	
	
	auto m3 = MenuItemImage::create("back.png", "back.png", this, menu_selector(SelectStone::ReturnMainSence));
	auto mm = Menu::create(m3, 0);

	mm->setScale(0.05);
	mm->setAnchorPoint(Vec2(0, 0));
	mm->setPosition(870, 100);
	addChild(mm);

	/*if (k)
	{
		getChildByTag(1)->setVisible(true);
		getChildByTag(2)->setVisible(false);
		k = 0;
	}
	else
	{
		getChildByTag(1)->setVisible(false);
		getChildByTag(2)->setVisible(true);
		k = 1;
	}*/

	if (ChessBoard::isdouble)
	{
		schedule(schedule_selector(SelectStone::WaitConnect), 1);
		auto l = Label::create("Matching in progress 0 ", "", 55);
		l->setPosition(490, 200);
		l->setTag(1);
		l->setScale(0.4);
		l->setColor(cocos2d::Color3B::Color3B(237, 236, 157));
		addChild(l);

		auto l1 = Label::create("You should red", "", 40);
		l1->setTag(3);
		l1->setVisible(false);
		l1->setPosition(480, 500);
		addChild(l1);
		
	}

	
	//SelectStoneColor(1);
	
}
void SelectStone::WaitConnect(float)
{
	//if (ChessBoard::isdouble == true)
	//{
	//	MsgisDouble msg;
	//	Clientclass::GetInstance()->SendData((char*)&msg);
	//}
	m_time++;
	char buff[50];
	sprintf(buff, "Matching in progress %d", m_time);
	((Label *)getChildByTag(1))->setString(buff);
	if (mflag == -1)
	{
		return;
	}
	else if (mflag == 1)
	{
		mflag = -1;
		ChessBoard::red = false;
		auto mchessboard = ChessBoard::createScene();
		Director::getInstance()->replaceScene(TransitionSplitRows::create(1, mchessboard));
		
	}
	else  if (mflag == 0)
	{
		mflag = -1;
		ChessBoard::red = true;
		auto mchessboard = ChessBoard::createScene();
		Director::getInstance()->replaceScene(TransitionSplitRows::create(1, mchessboard));
	
	}

}


void SelectStone::RedStone(Ref*)
{
	if (ChessBoard::isdouble)
	{
		MsgStoneColor msg;
		msg.red = true;
		Clientclass::GetInstance()->SendData((char*)&msg);
	}
	ChessBoard::red = true;
	auto mchessboard = ChessBoard::createScene();
	Director::getInstance()->replaceScene(TransitionSplitRows::create(1, mchessboard));
}
void SelectStone::BlackStone(Ref*)
{
	if (ChessBoard::isdouble)
	{
		MsgStoneColor msg;
		msg.red = false;
		Clientclass::GetInstance()->SendData((char*)&msg);
	}
	ChessBoard::red = false;
	auto mchessboard = ChessBoard::createScene();
	Director::getInstance()->replaceScene(TransitionSplitRows::create(1, mchessboard));
	return;
}
void SelectStone::ReturnMainSence(Ref*)
{
	Director::getInstance()->popScene();
}
void SelectStone::SelectStoneColor(bool b)
{
	
	if (b == true)
	{
		mflag = 1;

	}
	else
	{
		mflag = 0;
	}
	
	
}