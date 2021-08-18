#ifndef __ChessBoard_SCENE_H__
#define __ChessBoard_SCENE_H__

#include "cocos2d.h"
#include <SimpleAudioEngine.h>
#include <vector>
#include "../proj.win32/Stone.h"
#include "../Classes/Client/Clientclass.h"

#include "MsgType\MsgType.hpp"
using namespace CocosDenshion;


class SigleMachine;
class ChessBoard : public cocos2d::Layer, public cocos2d::CCTextFieldDelegate, ui::EditBoxDelegate
{
public:
	int m_time;  //倒计时
	int m_InitArry[10][9];
	int m_GamePross[10][9];
	float m_scale; //棋盘缩放的比例
	Stone *m_stone[32];
	bool m_flag;  	//m_flag==true 吃子
	vector<Stone*> m_Pross;
	int ii;   //上一次的棋子
	bool mcompetitor;//双人联网中对方下了，我才能下。（接收到数据以后为ture）
	Clientclass * m_client;
//public:

	static bool red;//先手判断
	static bool isdouble;//是双人联网
	static bool isSingleMachine;//人机对战
	static cocos2d::Scene* createScene();
	CREATE_FUNC(ChessBoard);
	ChessBoard();
    
	void InitStone();
	void InitBack();
	void StoneBindEventListen(cocos2d::Sprite *s, cocos2d::EventListenerTouchOneByOne * e);
	void Down(EventMouse *event);
	void MoveStone(int last,int i,int j);
	void GetResult();
    
	virtual void SetData(int last, int now, int i, int j);

    virtual bool init();
	void RegretStone();//悔棋

	
	void ReturnSelectStoneSence(Ref*);
	void SetText(char *str);
	void AddText();



	void CountDown(float);
	virtual void editBoxReturn(ui::EditBox* editBox);
	
	void PlayRose();

	bool mSingleMachine;	
	
};

#endif 


