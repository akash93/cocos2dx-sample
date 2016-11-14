#pragma once

#include "cocos2d.h"
#include "BallGrid.h"


USING_NS_CC;

class Game : public Layer{
	
public:
	Game();
	virtual ~Game();
	static Scene* createScene();
	virtual bool init() override;
	BallGrid* ball_grid;
	Size _screen_size;
	CREATE_FUNC(Game);
	void initGrid(bool is_resumed);
	virtual bool onTouchBegan(Touch* touch, Event* events) override;
	virtual void onTouchEnded(Touch* touch, Event* events) override;
	
};
