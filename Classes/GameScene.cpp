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
    _screen_size = Director::getInstance()->getVisibleSize();
    /* _player1 = PlayerSprite::gameSpriteWithFile("goku_ssgss.png"); */
    /* _player2 = PlayerSprite::gameSpriteWithFile("goku_ssgss.png"); */
    /* _player1->setPosition(Vec2(_screen_size.width*0.5,_screen_size.height*0.2 - _player1->radius()*2)); */
    /* _player2->setPosition(Vec2(_screen_size.width*0.5,_screen_size.height*0.7)); */
    /* _player1->setScale(0.2,0.2); */
    /* _player2->setScale(0.2,0.2); */
    /*  this->addChild(_player1,1); */
    /*  this->addChild(_player2,1); */ 
    
    auto start_x = _screen_size.width*0.2;
    auto start_y = _screen_size.height*0.5;
    int distance_measure = 15;

    std::vector<std::string> _sprite_names = {"blue_ball.png","yellow_ball.png","purple_ball.png","orange_ball.png"};
    std::srand(std::time(NULL));
    for(int i = 0; i < 4; i++){
        std::vector<BallSprite*> rows;
        for(int j = 0; j < 5; j++){
            int random = std::rand() % 4;
            BallSprite* ball_sprite = BallSprite::gameSpriteWithFile(_sprite_names.at(random).c_str());
            ball_sprite->setPosition(Vec2(start_x + j*ball_sprite->radius()*distance_measure,start_y + i*ball_sprite->radius()*distance_measure));
            ball_sprite->setScale(8);
            ball_sprite->color = static_cast<Color>(random);
            rows.push_back(ball_sprite);
            this->addChild(ball_sprite,1);
        }
        ball_sprites.push_back(rows);
    } 

    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(Game::onTouchBegan,this);
    listener->onTouchEnded = CC_CALLBACK_2(Game::onTouchEnded,this);
    listener->onTouchMoved = CC_CALLBACK_2(Game::onTouchMoved,this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);

    _player_score_label = Label::createWithSystemFont("Score: 0","Arial",80);
    _player_score_label->setPosition(Vec2(_screen_size.width* 0.2, _screen_size.height*0.2));
    _player_score_label->setTextColor(Color4B::WHITE);
    this->addChild(_player_score_label,1);
    this->scheduleUpdate();
      
    return true;
}

bool Game::onTouchBegan(Touch* touch, Event* event){
    if(touch!= nullptr){
        auto tap = touch->getLocation();
        for(auto rows : ball_sprites){
            for(auto ball_sprite: rows){
                if(ball_sprite->getBoundingBox().containsPoint(tap)){
                    auto tint_action = TintTo::create(2.0f, 120.0f, 232.0f, 254.0f);
                    ball_sprite->runAction(tint_action);
                    return true;
                }
            }
        }
    }
    return false;
}

void Game::onTouchMoved(Touch* touch, Event* event){

}

void Game::onTouchEnded(Touch* touch,Event* event){

}

void Game::updateScore(){

}

void Game::update(float dt){

}


