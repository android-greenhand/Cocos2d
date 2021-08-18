#ifndef __SELECTSTONE_SCENE_H__
#define __SELECTSTONE_SCENE_H__

#include "cocos2d.h"
#include "MsgType\MsgType.hpp"
class SelectStone : public cocos2d::Layer
{
	int mflag;//标记已经接受服务器发送的棋子
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
	CREATE_FUNC(SelectStone);
	SelectStone();
	int m_time;
	void RedStone(Ref*);
	void BlackStone(Ref*);
	void init_desk();
	void ReturnMainSence(Ref*);
	void WaitConnect(float);
	void SelectStoneColor(bool b);
};

#endif // __HELLOWORLD_SCENE_H__
