#include "GameScene.h"
USING_NS_CC;

Game::Game(void){

}

Game::~Game(void){

}

Scene* Game::createScene(){
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Game::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Game::init(){
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    _player_score = 0;
    _screen_size = Director::getInstance()->getWinSize();
    _player1 = PlayerSprite::gameSpriteWithFile("goku_ssgss.png");
    _player2 = PlayerSprite::gameSpriteWithFile("goku_ssgss.png");
    _player1->setPosition(Vec2(_screen_size.width*0.5,_screen_size.height*0.2 - _player1->radius()*2));
    _player2->setPosition(Vec2(_screen_size.width*0.5,_screen_size.height*0.7));
    _player1->setScale(0.2,0.2);
    _player2->setScale(0.2,0.2);
     this->addChild(_player1,1); 
     this->addChild(_player2,1); 
    
    auto start_x = _screen_size.width*0.2;
    auto start_y = _screen_size.height*0.4;
    int distance_measure = 10;

    std::vector<std::string> _sprite_names = {"blue_ball.png","yellow_ball.png","purple_ball.png","orange_ball.png"};
    std::vector<std::vector<BallSprite*>> ball_sprites;
    for(int i = 0; i < 3; i++){
        std::vector<BallSprite*> rows;
        for(int j = 0; j < 4; j++){
            int random = std::rand() % 4;
            BallSprite* ball_sprite = BallSprite::gameSpriteWithFile(_sprite_names.at(random).c_str());
            ball_sprite->setPosition(Vec2(start_x + j*ball_sprite->radius()*distance_measure,start_y + i*ball_sprite->radius()*distance_measure));
            ball_sprite->setScale(8);
            rows.push_back(ball_sprite);
            this->addChild(ball_sprite,1);
        }
        ball_sprites.push_back(rows);
    } 
      
    return true;
}

bool Game::onTouchBegan(Touch* touch, Event* event){

}

void Game::onTouchMoved(Touch* touch, Event* event){

}

void Game::onTouchEnded(Touch* touch,Event* event){

}

void Game::updateScore(){

}

void Game::update(float dt){

}


