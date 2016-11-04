#include "GameScene.h"
#include "BallGrid.h"
USING_NS_CC;

#define NUM_ROWS  5
#define NUM_COLS  4

Game::Game(void){}

Game::~Game(void){}

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
	if ( !Layer::init() ){
		return false;
	}
	
	//Initialize rand generator and display variables
	std::srand(time(NULL));
	_player_score = 0;
	_screen_size = Director::getInstance()->getVisibleSize();
	
	// Set spacing and starting point of grid
	auto start_x = _screen_size.width * 0.2;
	auto start_y = _screen_size.height * 0.5;
	int distance_measure = 25;
	
	// Load the sprite frame cache
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ball_sprites.plist");

	// Generate grid
	ball_grid = new BallGrid();
	ball_grid->generateGrid(NUM_COLS, NUM_ROWS );
	for (int i = 0; i < NUM_ROWS; i++){
		for (int j = 0; j < NUM_COLS; j++) {
			auto x_cord = start_x + j*ball_grid->ball_sprites[i][j]->radius() * distance_measure;
			auto y_cord = start_y + i*ball_grid->ball_sprites[i][j]->radius() * distance_measure;
			ball_grid->ball_sprites[i][j]->setPosition(Vec2(x_cord, y_cord));
			this->addChild(ball_grid->ball_sprites[i][j], 1);
		}
	}

	// Register touch listeners
	auto listener = EventListenerTouchOneByOne::create();

	listener->onTouchBegan = CC_CALLBACK_2(Game::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(Game::onTouchEnded, this);
	listener->onTouchMoved = CC_CALLBACK_2(Game::onTouchMoved, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


	_player_score_label = Label::createWithSystemFont("Score: 0", "Arial", 80);
	_player_score_label->setPosition(Vec2(_screen_size.width * 0.2, _screen_size.height * 0.2));
	_player_score_label->setTextColor(Color4B::WHITE);
	this->addChild(_player_score_label, 1);
	
	this->scheduleUpdate();
	
	return true;
}


bool Game::onTouchBegan(Touch* touch, Event* event){
	//Check if touch was valid
	return touch!=nullptr;
}

void Game::onTouchMoved(Touch* touch, Event* event){
}

void Game::onTouchEnded(Touch* touch, Event* event){
	//TODO move grid manipulation steps here so that the change happens when user has lifted finger
	if (touch!= nullptr){ 
		auto tap = touch->getLocation();
		int chosen_idx	= -1;

		//Check if ball in first row was touched
		for (int i = 0; i < NUM_COLS; i++){
			if (ball_grid->ball_sprites[0][i]->getBoundingBox().containsPoint(tap)){
			   chosen_idx = ball_grid->ball_sprites[0][i]->id; 
			   break;
			}
		}
		
		// If yes then perform then find the path and generate a new grid after that
		// TODO add animations to highlight the path and move the grid generation to onTouchEnded
		if (chosen_idx != -1){
			// Generate the list of chosen balls and burst balls
			ball_grid->setPath(chosen_idx);

			// Animate the balls and manipulate the grid
			ball_grid->generateNewGrid();

			// Add the new balls to the scene graph
			for (auto ball : ball_grid->balls_to_be_added){
				this->addChild(ball, 1);
			}
		}
	}
}

void Game::update(float dt){

}


