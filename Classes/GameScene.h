#pragma once

#include "cocos2d.h"
#include "PlayerSprite.h"
#include "BallGrid.h"


USING_NS_CC;

class Game : public Layer{
    
public:
    Game();
    virtual ~Game();
    static Scene* createScene();
    virtual bool init() override;
    PlayerSprite* _player1;
    PlayerSprite* _player2;
    BallGrid* ball_grid;

    Label* _player1_name_label;
    Label* _player2_name_label;
    
    Label* _player_score_label;
    Size _screen_size;

    int _player_score;
    void updateScore();
    CREATE_FUNC(Game);

    virtual bool onTouchBegan(Touch* touch, Event* events) override;
    virtual void onTouchMoved(Touch* touch, Event* events) override;
    virtual void onTouchEnded(Touch* touch, Event* events) override;
    
    void update(float dt) override;
    
};
