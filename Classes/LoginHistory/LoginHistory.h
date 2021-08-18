#ifndef __LOGINHISTORY_SCENE_H__
#define __LOGINHISTORY_SCENE_H__
#include<SimpleAudioEngine.h>
#include "cocos2d.h"

using namespace CocosDenshion;
class LoginHistory : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
	CREATE_FUNC(LoginHistory);
	void ReturnMainSence(Ref*);

	

};

#endif // __HELLOWORLD_SCENE_H__
