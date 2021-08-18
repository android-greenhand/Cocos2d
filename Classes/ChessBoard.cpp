#include "ChessBoard.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
//#include "SingleMachie\SigleMachine.h"

#include "proj.win32\SigleMachine.h"
using namespace cocostudio::timeline;
bool ChessBoard::red = true;
bool ChessBoard::isdouble=false;
bool ChessBoard::isSingleMachine=false;
ChessBoard::ChessBoard()
{
	int InitArry[10][9] = {
		{ 1, 2, 3, 4, 5, 4, 3, 2, 1 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 6, 0, 0, 0, 0, 0, 6, 0 },
		{ 7, 0, 7, 0, 7, 0, 7, 0, 7 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 27, 0, 27, 0, 27, 0, 27, 0, 27 },
		{ 0, 26, 0, 0, 0, 0, 0, 26, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 21, 22, 23, 24, 25, 24, 23, 22, 21 },
	};
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			m_InitArry[i][j] = InitArry[i][j];
			m_GamePross[i][j] = InitArry[i][j];;
		}
	}
	m_scale = 636.0 / 1101; //棋盘缩放的比例
	ii = -1;      //上一次的棋子
	m_flag = true;  	//m_flag==true 吃子
	m_time = 60;  
	mcompetitor = true;

	if (isdouble)
	{
		m_client = Clientclass::GetInstance();
		Clientclass::GetInstance()->SetChessBoard(this);
	}
	else
	{
		m_client = NULL;
	}
	mSingleMachine = false;
}
Scene* ChessBoard::createScene()
{
	auto scene = Scene::create();
	auto layer = ChessBoard::create();
	scene->addChild(layer);
	return scene;
}
bool ChessBoard::init()
{
	if (!Layer::init())
	{
		return false;
	}
	InitBack();
	InitStone();
	return true;
}
void ChessBoard::InitStone()
{
	int k = 0;// 记录那个棋子
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("stone.plist");
	auto e = EventListenerTouchOneByOne::create();
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (m_InitArry[i][j] == 0)
			{
				continue;
			}
			auto s = Sprite::create("bche.png");
			StoneBindEventListen(s, e);
			switch (m_InitArry[i][j])
			{
			case 1:
			{
					  s->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("bche.png"));
					  ChessCarStone * c = new ChessCarStone(m_InitArry[i][j], i, j, s,100);
					  m_stone[k++] = c;
					  break;
			}
			case 2:
			{
					  s->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("bma.png"));
					  ChessHorseStone * c = new ChessHorseStone(m_InitArry[i][j], i, j, s,50);
					  m_stone[k++] = c;
					  break;
			}
			case 3:
			{
					  s->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("bxiang.png"));
					  ChessElephantStone * c = new ChessElephantStone(m_InitArry[i][j], i, j, s,30);
					  m_stone[k++] = c;
					  break;
			}
			case 4:
			{
					  s->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("bshi.png"));
					  ChessSoldierStone * c = new ChessSoldierStone(m_InitArry[i][j], i, j, s,30);
					  m_stone[k++] = c;
					  break;
			}
			case 5:
			{
					  s->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("bjiang.png"));
					  ChessGeneralStone * c = new ChessGeneralStone(m_InitArry[i][j], i, j, s,1500);
					  m_stone[k++] = c;
					  break;
			}
			case 6:
			{
					  s->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("bpao.png"));
					  ChessCannonStone * c = new ChessCannonStone(m_InitArry[i][j], i, j, s,50);
					  m_stone[k++] = c;
					  break;
			}
			case 7:
			{
					  s->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("bzu.png"));
					  ChessObiitStone * c = new ChessObiitStone(m_InitArry[i][j], i, j, s,10);
					  m_stone[k++] = c;
					  break;
			}
			case 21:
			{
					   s->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("rche.png"));
					   ChessCarStone * c = new ChessCarStone(m_InitArry[i][j], i, j, s,100);
					   m_stone[k++] = c;
					   break;
			}
			case 22:
			{
					   s->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("rma.png"));
					   ChessHorseStone * c = new ChessHorseStone(m_InitArry[i][j], i, j, s,50);
					   m_stone[k++] = c;
					   break;
			}
			case 23:
			{
					   s->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("rxiang.png"));
					   ChessElephantStone * c = new ChessElephantStone(m_InitArry[i][j], i, j, s,30);
					   m_stone[k++] = c;
					   break;
			}
			case 24:
			{
					   s->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("rshi.png"));
					   ChessSoldierStone * c = new ChessSoldierStone(m_InitArry[i][j], i, j, s,30);
					   m_stone[k++] = c; break;
			}
			case 25:
			{
					   s->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("icon.png"));//plist生成有错
					   ChessGeneralStone * c = new ChessGeneralStone(m_InitArry[i][j], i, j, s,1500);
					   m_stone[k++] = c;
					   break;
			}
			case 26:
			{
					   s->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("rpao.png"));
					   ChessCannonStone * c = new ChessCannonStone(m_InitArry[i][j], i, j, s,50);
					   m_stone[k++] = c;
					   break;
			}
			case 27:
			{
					   s->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("rbing.png"));
					   ChessObiitStone * c = new ChessObiitStone(m_InitArry[i][j], i, j, s,10);
					   m_stone[k++] = c;
					   break;
			}
			default:break;
			}
			ccBezierConfig bezier;
			bezier.controlPoint_1 = Point(0, 0);
			bezier.controlPoint_2 = Point(400, 300);
			bezier.endPosition = Point(1 + 112.08 * m_scale + j * 110 * m_scale, 60 * m_scale + 110 * (9 - i) * m_scale);
			auto b = BezierTo::create(1.5, cocos2d::ccBezierConfig(bezier));
			s->runAction(b);
			SimpleAudioEngine::getInstance()->playEffect("INint.mp3");// 播放声音

			addChild(s);
		}
	}
}
void ChessBoard::InitBack()
{
	//背景
	auto s = Sprite::create("floor.jpg");
	s->setAnchorPoint(Vec2(0, 0));
	s->setScale(Director::getInstance()->getWinSize().width / s->getContentSize().width, Director::getInstance()->getWinSize().height / s->getContentSize().height);
	addChild(s);

	//棋盘
	auto s1 = Sprite::create("background1.png");
	s1->setAnchorPoint(Vec2(0, 0));
	s1->setPosition(1, 0.5);
	s1->setScale(m_scale);
	addChild(s1);
	auto e = EventListenerMouse::create();
	e->onMouseDown = CC_CALLBACK_1(ChessBoard::Down, this); //cc_callback_1和cc_callback_2的区别
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(e, s1);

	//头像
	auto s2 = Sprite::create("bkg1.png");
	auto s3 = Sprite::create("bkg2.png");
	s2->setPosition(700, 150);
	s3->setPosition(700, 600);
	addChild(s2);
	addChild(s3);

	//选框
	auto s4 = Sprite::create("selected.png");
	auto s5 = Sprite::create("selected.png");
	s4->setScale(90.0 / 70, 68.0 / 70);
	s5->setScale(90.0 / 70, 68.0 / 70);
	s4->setPosition(700, 150);
	s5->setPosition(700, 600);
	s4->setVisible(!red);
	s5->setVisible(red);
	s4->setTag(1);
	s5->setTag(2);
	addChild(s4);
	addChild(s5);

	//悔棋
	auto m1 = MenuItemImage::create("RegretStone.png", "RegretStone.png", [&](Ref*)
	{
		if (!m_Pross.empty())
		{
			RegretStone();
		}
		if (isdouble)
		{
			MsgRegretStone msgregretstone;
			m_client->SendData((char *)&msgregretstone);
		}
	});
	m1->setScale(0.34);
	//返回
	auto m2 = MenuItemImage::create("back.png", "back.png", [](Ref*){Director::getInstance()->popScene(); });
	m2->setScale(0.08);
	auto m = Menu::create(m1, m2, 0);
	m->alignItemsVertically();
	m->setAnchorPoint(Vec2(0, 0));
	m->setPosition(870, 40);
	m->setScale(0.5);
	addChild(m);

	//定时器 1
	schedule(schedule_selector(ChessBoard::CountDown), 1); //倒计时
	auto l = Label::create("60 ", "", 80);
	l->setPosition(800, 600);
	l->setTag(5);
	l->setScale(0.4);
	l->setColor(cocos2d::Color3B::Color3B(237, 236, 157));
	addChild(l);

	//玫瑰花
	auto rose = Sprite::create("rose1.png");
	addChild(rose);
	rose->setPosition(Vec2(760, 30));
	rose->setName("rose");
	rose->setOpacity(0);
	rose->setScale(0.05);

	//玫瑰花菜单
	auto mrose = MenuItemImage::create("rose1.png", "rose1.png", [&](Ref*)
	{
		if (isdouble)
		{
			MsgRose msgrose;
			m_client->SendData((char *)&msgrose);
		}
		else
		{
			PlayRose();
		}
	});
	mrose->setScale(0.1);
	auto menurose = Menu::create(mrose, 0);
	menurose->setAnchorPoint(Vec2(0, 0));
	menurose->setPosition(760, 30);
	addChild(menurose);

	//如果是双人 就添加文本
	if (isdouble)
		AddText();
}
void ChessBoard::AddText()
{
	//UserDefault::getInstance

	auto text = ui::EditBox::create(CCSizeMake(140, 40), "chat.png");
	text->setFont("yes.ttf", 15);
	text->setFontColor(cocos2d::Color3B::GREEN);
	text->setPosition(Vec2(870, 100));
	text->setInputMode(ui::EditBox::InputMode::ANY);
	text->setReturnType(ui::EditBox::KeyboardReturnType::SEND);
	addChild(text);
	text->setDelegate(this);
	text->setMaxLength(15);
	text->setName("对话框");

	auto dic = Dictionary::createWithContentsOfFile("CHN_Strings.xml");
	auto str1 = (String *)dic->objectForKey("string7");

	auto laa = Label::create(str1->getCString(), "", 20);
	addChild(laa);
	laa->setPosition(Vec2(870, 200));
	laa->setColor(cocos2d::Color3B::BLACK);

	auto la = Label::create("ChinaChess", "", 20);
	addChild(la);
	la->setPosition(Vec2(870, 170));
	la->setTag(4);
	la->setColor(cocos2d::Color3B::YELLOW);
}

void ChessBoard::MoveStone(int last, int i, int j)
{
	//有上一个棋子，且从StoneBindEventListen（）函数过来，可以吃子
	if (m_flag&&last!=-1)
	{
		m_stone[last]->s->setVisible(false);
		m_Pross.push_back(m_stone[last]);
	}
	//移动
	auto m = MoveTo::create(0.3, Vec2(1 + 112.08 * m_scale + j * 110 * m_scale, 60 * m_scale + 110 * (9 - i)* m_scale));
	m_stone[ii]->s->runAction(m);
	m_stone[ii]->s->setScale(1);
	//更新棋子自己的路径
	m_stone[ii]->m_GameArry.push_back(make_pair(i, j));

	//更新游戏中的数组
	m_GamePross[m_stone[ii]->m_From.first][m_stone[ii]->m_From.second] = 0;
	m_GamePross[i][j] = m_stone[ii]->m_k;

	//更新棋子中的坐标
	m_stone[ii]->m_From = make_pair(i, j);
	//把棋子放到棋盘对象里，以实现悔棋
	m_Pross.push_back(m_stone[ii]);
	//上一个棋子继续置为-1
	ii = -1;
	
	//去判断输赢
	GetResult();

	//如果不是双人就red取反，
	
	if (!isdouble)
	{
		red = !red;
		mSingleMachine = !mSingleMachine;
	}
	else
	{
		mcompetitor = false;
	}
	m_time = 60;
	//落子声音
	SimpleAudioEngine::getInstance()->playEffect("2.wav");

	if (isSingleMachine&&mSingleMachine)
	{
		SigleMachine  SigleMachine(this);
		SigleMachine.getresult();
		
	}


}
void ChessBoard::GetResult()
{
	int k1 = 0;
	int k2 = 0;
	for (int i = 0; i < 10; i++)//****哈希算法
	{
		for (int j = 0; j < 9; j++)
		{
			if (m_GamePross[i][j] == 5)
			{
				k1 = 1;
			}
			if (m_GamePross[i][j] == 25)
			{
				k2 = 1;
			}
		}

	}
	auto dic = Dictionary::createWithContentsOfFile("CHN_Strings.xml");
	auto str1 = (String *)dic->objectForKey("string1");//红棋赢
	auto str2 = (String *)dic->objectForKey("string2");//黑棋赢
	
	auto l = Label::create(str1->getCString(), "", 50);
	l->setPosition(500, 300);
	l->setColor(cocos2d::Color3B::YELLOW);
	if (k1&&!k2)//黑棋赢
	{
		l->setString(str2->getCString());
		addChild(l);
		this->pause();
		this->stopAllActions();
		SimpleAudioEngine::getInstance()->playEffect("win.mp3");
	}
	else if (k2&&!k1)
	{
		addChild(l);
		this->pause();
		this->stopAllActions();
		SimpleAudioEngine::getInstance()->playEffect("win.mp3");
	}

}
void ChessBoard::Down(EventMouse *event)
{
	//m_flag 
	if(m_flag||ii==-1)
	{
		m_flag = false;
		return;
	}
	m_scale = 636.0 / 1101;
	int a = 110 * m_scale;//间隔
	auto p = event->getLocation() - Vec2(1 + 112.08 * m_scale,30);
	int x = (p.x + a / 2.0) / a;
	int y = (p.y + a / 2.0) / a;
	//点击的点是否在棋盘里
	if (x<0 || x > 8 || y > 9 || y<0)
	{
		return ;
	}
	int i = y;
	int j = x;
	if (m_stone[ii]->gular(m_GamePross, make_pair(i, j)))
	{
		if (isdouble)
		{
			MsgStone msgstone;
			msgstone.last_stone = -1;
			msgstone.now_stone = ii;
			msgstone.i = i;
			msgstone.j = j;
			m_client->SendData((char *)&msgstone);
		}
		MoveStone(-1,i, j);		
	}
}
void ChessBoard::StoneBindEventListen(Sprite *s, EventListenerTouchOneByOne * e1)
{
	//红色先手
	e1->onTouchBegan = [&](Touch* t,Event *e)
	{
		if (isdouble&&mcompetitor == false)
		{
			return true;
		}
		if (e->getCurrentTarget()->boundingBox().containsPoint(t->getLocation()))
		{
			
			for (int i = 0; i < 32; i++)
			{
				if (e->getCurrentTarget() == m_stone[i]->s&&m_stone[i]->s->isVisible())
				{
					m_flag = true;
					if (m_stone[i]->m_IsRed != red)
					{
						if (ii != -1)
						{
							if (m_stone[ii]->gular(m_GamePross, m_stone[i]->m_From))
							{
								if (isdouble)
								{
									MsgStone msgstone;
									msgstone.last_stone = i;
									msgstone.now_stone = ii;
									msgstone.i = m_stone[i]->m_From.first;
									msgstone.j = m_stone[i]->m_From.second;

									m_client->SendData((char *)&msgstone);
								}
								MoveStone(i,m_stone[i]->m_From.first, m_stone[i]->m_From.second);
							}
						}
						
						return  true;
					}
					
					if (ii == -1)
					{
						m_stone[i]->s->setScale(1.5);
						ii = i;
					}
					else if (m_stone[ii]->m_IsRed == m_stone[i]->m_IsRed)
					{
						m_stone[ii]->s->setScale(1);
						m_stone[i]->s->setScale(1.5);
						ii = i;
					}
				}
			}
		}
		return true;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(e1->clone(), s);
}

void ChessBoard::editBoxReturn(ui::EditBox* editBox) //编辑框的函数send
{
	MsgTalking msgtalking;
	msgtalking.SetText(editBox->getText());
	m_client->SendData((char *)&msgtalking);
}
void ChessBoard::SetText(char *str)
{
	Label *l = (Label*)getChildByTag(4);
	l->setString(str);
}
void ChessBoard::ReturnSelectStoneSence(Ref*)
{
    red = true;
	isdouble = false;
	isSingleMachine = false;
	this->cleanup();
	Director::getInstance()->popScene();
}

void ChessBoard::SetData(int last, int now, int i, int j)
{
	ii = now;
	if (last != -1)
	{
		m_flag = true;
	}
	MoveStone(last, i, j);
	mcompetitor = true;
}
void ChessBoard::RegretStone()//悔棋
{
	if (m_Pross.empty())
	{
		return;
	}
	red = !red;
	Stone * s_now = m_Pross.back();
	m_Pross.pop_back();
	if (!m_Pross.empty())
	{
		Stone * s_last = m_Pross.back();
		if (!s_last->s->isVisible())
		{
			s_last->s->setVisible(true);
			m_GamePross[s_last->m_From.first][s_last->m_From.second] = s_last->m_k;
			s_now->m_GameArry.pop_back();
			m_GamePross[s_now->m_GameArry.back().first][s_now->m_GameArry.back().second] = s_now->m_k;
			s_now->s->setPosition(1 + 112.08 * m_scale + s_now->m_GameArry.back().second * 110 * m_scale, 60 * m_scale + 110 * (9 - s_now->m_GameArry.back().first) * m_scale);
			s_now->m_From = s_now->m_GameArry.back();
			m_Pross.pop_back();
			return;
		}
	}
	m_GamePross[s_now->m_GameArry.back().first][s_now->m_GameArry.back().second] = 0;
	s_now->m_GameArry.pop_back();
	s_now->s->setPosition(1 + 112.08 * m_scale + s_now->m_GameArry.back().second * 110 * m_scale, 60 * m_scale + 110 * (9 - s_now->m_GameArry.back().first) * m_scale);
	m_GamePross[s_now->m_GameArry.back().first][s_now->m_GameArry.back().second] = s_now->m_k;
	s_now->m_From = s_now->m_GameArry.back();
}
void ChessBoard::CountDown(float)
{
	//更新选框
	if (!red)
	{
		getChildByTag(1)->setVisible(true);
		getChildByTag(2)->setVisible(false);

	}
	else
	{
		getChildByTag(1)->setVisible(false);
		getChildByTag(2)->setVisible(true);
	}

	//显示倒计时
	m_time--;
	char buff[50];
	sprintf(buff, "%d", m_time);
	((Label *)getChildByTag(5))->setString(buff);

	//倒计时<0，游戏结束
	if (m_time > 0)
	{
		return;
	}
	auto dic = Dictionary::createWithContentsOfFile("CHN_Strings.xml");
	auto str1 = (String *)dic->objectForKey("string1");//红棋赢
	auto str2 = (String *)dic->objectForKey("string2");//黑棋赢

	auto l = Label::create(str1->getCString(), "", 50);
	l->setPosition(500, 300);
	l->setColor(cocos2d::Color3B::YELLOW);
	if (red)//黑棋赢
	{
		l->setString(str2->getCString());
		addChild(l);
		this->pause();
		this->stopAllActions();
		SimpleAudioEngine::getInstance()->playEffect("win.mp3");
	}
	else 
	{
		addChild(l);
		this->pause();
		this->stopAllActions();
		SimpleAudioEngine::getInstance()->playEffect("win.mp3");
	}
}
void ChessBoard::PlayRose()
{
	Sprite * s = (Sprite*)getChildByName("rose");
	ccBezierConfig bezier;
	bezier.controlPoint_1 = Point(0, 0);
	bezier.controlPoint_2 = Point(400, 300);
	bezier.endPosition = Point(480,300);
	auto b = BezierTo::create(2, cocos2d::ccBezierConfig(bezier));
	auto scale = ScaleTo::create(2,1);
	auto fadein = FadeIn::create(2);
	auto sp = Spawn::create(fadein,b, scale, 0);
	auto fadeout = FadeOut::create(2);
	auto sequence = Sequence::create(sp, fadeout,  0);
	s->runAction(sequence);
	
}
