#pragma once

#include "cocos2d.h"
USING_NS_CC;

class HelloWorld : public Layer{
    
public:
    static Scene* createScene();
    virtual bool init();
    
    virtual bool onTouchBegan(Touch*,Event*);
    virtual void onTouchEnded(Touch*,Event*);
    virtual void onTouchMoved(Touch*,Event*);
    virtual void onTouchCancelled(Touch*,Event*);
    
    CREATE_FUNC(HelloWorld);
    
private:
    Label* touchLabel;
    
};
