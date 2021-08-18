#ifndef __HELP_SCENE_H__
#define __HELP_SCENE_H__

#include "cocos2d.h"
#include "MainInterface\MainInterface.h"
#include "MsgType\MsgType.hpp"
class Login : public cocos2d::CCLayer, public cocos2d::CCTextFieldDelegate
{
	MsgLogin  msglogin;
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
	CREATE_FUNC(Login);
	void MenuSendLogin(Ref*);
	void EnterMainInterface(float);
	void Quit(Ref*);
	bool mloginreplay;
	
};

#endif // __HELLOWORLD_SCENE_H__
