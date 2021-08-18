#pragma once
#include <iostream>
#include <vector>
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"


USING_NS_CC;

using namespace cocostudio::timeline;
using namespace std;
class Stone
{
public:
	int m_k;
	pair<int, int> m_Init;
	pair<int, int> m_From;
	bool m_IsRed;
	vector<pair<int, int>> m_GameArry;
	cocos2d::Sprite * s;
	int value;//·ÖÊý
public:
	virtual bool gular(int game_arr[10][9], pair<int, int> To)=0;
	Stone(int a,int i, int j,cocos2d::Sprite * s,int  v);
	virtual  ~Stone();
};

class ChessCarStone :public Stone
{
public:
	ChessCarStone(int a, int i, int j, cocos2d::Sprite * s,int  v) :Stone(a, i, j, s,v){}
	virtual bool  gular(int game_arr[10][9], pair<int, int> To);
};

class ChessHorseStone :public Stone
{
public:
	ChessHorseStone(int a, int i, int j, cocos2d::Sprite * s,int  v) :Stone(a, i, j, s,v){}
	virtual bool gular(int game_arr[10][9], pair<int, int> To);
};

class ChessElephantStone :public Stone
{
public:
	ChessElephantStone(int a, int i, int j, cocos2d::Sprite * s,int  v) :Stone(a, i, j, s,v){}
	virtual bool  gular(int game_arr[10][9], pair<int, int> To);
};

class ChessSoldierStone :public Stone
{
public:
	ChessSoldierStone(int a, int i, int j, cocos2d::Sprite * s,int  v) :Stone(a, i, j, s,v)	{}
	virtual bool gular(int game_arr[10][9], pair<int, int> To);
};

class ChessGeneralStone :public Stone
{
public:
	ChessGeneralStone(int a, int i, int j, cocos2d::Sprite * s,int  v) :Stone(a, i, j, s,v){}
	virtual bool  gular(int game_arr[10][9], pair<int, int> To);
};

class ChessCannonStone :public Stone
{
public:
	ChessCannonStone(int a, int i, int j, cocos2d::Sprite * s,int  v) :Stone(a, i, j, s,v){}
	virtual bool  gular(int game_arr[10][9], pair<int, int> To);
};

class ChessObiitStone :public Stone
{
public:
	ChessObiitStone(int a, int i, int j, cocos2d::Sprite * s,int  v) :Stone(a, i, j, s,v){}
	virtual bool  gular(int game_arr[10][9], pair<int, int> To);
};


