#include "GameScene.h"
#include "BallGrid.h"
USING_NS_CC;

#define NUM_ROWS  5
#define NUM_COLS  4

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
    ball_grid = new BallGrid();
    ball_grid->generateGrid(NUM_COLS, NUM_ROWS, _sprite_names);
    for(int i = 0; i < NUM_ROWS; i++){
        for (int j = 0; j < NUM_COLS; j++) {
            auto x_cord = start_x + j*ball_grid->ball_sprites[i][j]->radius() * distance_measure;
            auto y_cord = start_y + i*ball_grid->ball_sprites[i][j]->radius() * distance_measure;
            ball_grid->ball_sprites[i][j]->setPosition(Vec2(x_cord,y_cord));
            ball_grid->ball_sprites[i][j]->setScale(8);
            this->addChild(ball_grid->ball_sprites[i][j],1);
        }
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
        int chosen_idx  = -1;
        for(int i = 0; i < NUM_COLS; i++){
            if(ball_grid -> ball_sprites[0][i]->getBoundingBox().containsPoint(tap)){
               chosen_idx = ball_grid -> ball_sprites[0][i]->id; 
               break;
            }
        }
        
        if(chosen_idx != -1){
            ball_grid->setPath(chosen_idx);
            
            for (int i = 0; i < NUM_ROWS; i++){
                for (int j = 0; j < NUM_COLS; j++){
                    auto chosen_action = TintTo::create(0.5f, 0.0f, 0.0f, 0.0f);
                    auto burst_action = ScaleTo::create(0.5f, 2.0f);
                    if(std::find(ball_grid->chosen_path.begin(),ball_grid->chosen_path.end(),ball_grid->ball_sprites[i][j]->id) != ball_grid->chosen_path.end()){
                        ball_grid->ball_sprites[i][j]->runAction(chosen_action);
                        continue;
                    }
                    if(std::find(ball_grid->burst_balls.begin(),ball_grid->burst_balls.end(),ball_grid->ball_sprites[i][j]->id) != ball_grid->burst_balls.end()){
                        ball_grid->ball_sprites[i][j]->runAction(burst_action);
                        continue;
                    }
                }
            }
            return true;
        }

        return false;

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


