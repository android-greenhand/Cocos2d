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
	int m_time;  //����ʱ
	int m_InitArry[10][9];
	int m_GamePross[10][9];
	float m_scale; //�������ŵı���
	Stone *m_stone[32];
	bool m_flag;  	//m_flag==true ����
	vector<Stone*> m_Pross;
	int ii;   //��һ�ε�����
	bool mcompetitor;//˫�������жԷ����ˣ��Ҳ����¡������յ������Ժ�Ϊture��
	Clientclass * m_client;
//public:

	static bool red;//�����ж�
	static bool isdouble;//��˫������
	static bool isSingleMachine;//�˻���ս
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
	void RegretStone();//����

	
	void ReturnSelectStoneSence(Ref*);
	void SetText(char *str);
	void AddText();



	void CountDown(float);
	virtual void editBoxReturn(ui::EditBox* editBox);
	
	void PlayRose();

	bool mSingleMachine;	
	
};

#endif 


