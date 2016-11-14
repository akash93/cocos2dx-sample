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
	_screen_size = Director::getInstance()->getVisibleSize();
	
	// Load the sprite frame cache
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ball_sprites.plist");
	//initialize the grid
	bool is_resumed = UserDefault::getInstance()->getBoolForKey("is_resumed");
	initGrid(is_resumed);

	// Register touch listeners
	auto listener = EventListenerTouchOneByOne::create();

	listener->onTouchBegan = CC_CALLBACK_2(Game::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(Game::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

// Initialize the grid and position the balls. 
// @param is_resumed: Defines whether to start a new game or to resume a previously saved game
void Game::initGrid(bool is_resumed){
	// Set spacing and starting point of grid
	auto start_x = _screen_size.width * 0.2; // Specify the starting point of the grid
	auto start_y = _screen_size.height * 0.5;
	int distance_measure = 25; // Measure of the spacing between the balls.


	// Generate grid
	ball_grid = new BallGrid();
	ball_grid->_grid_origin = Point(start_x, start_y);
	if(is_resumed){
		ball_grid->resumeGrid(NUM_COLS, NUM_ROWS);
	}
	else{
		ball_grid->generateGrid(NUM_COLS, NUM_ROWS);
	}

	// Position the balls in the grid
	for (int i = 0; i < NUM_ROWS; i++){
		for (int j = 0; j < NUM_COLS; j++) {
			auto x_cord = start_x + j*ball_grid->ball_sprites[i][j]->radius() * distance_measure;
			auto y_cord = start_y + i*ball_grid->ball_sprites[i][j]->radius() * distance_measure;
			ball_grid->ball_sprites[i][j]->setPosition(Vec2(x_cord, y_cord));
			this->addChild(ball_grid->ball_sprites[i][j], 1);
		}
	}

	//Setup grid parameters
	ball_grid->_grid_height = ball_grid->ball_sprites[NUM_ROWS - 1][0]->getPositionY();
	ball_grid->_grid_width = ball_grid->ball_sprites[0][NUM_COLS - 1]->getPositionX();
	ball_grid->_grid_step_x = ball_grid->ball_sprites[0][1]->getPositionX() - ball_grid->ball_sprites[0][0]->getPositionX();
	ball_grid->_grid_step_y = ball_grid->ball_sprites[1][0]->getPositionY() - ball_grid->ball_sprites[0][0]->getPositionY();
}

// Handles calculating the chosen and burst balls based on the user choice
// @return : true if the event has been handled and false otherwise
bool Game::onTouchBegan(Touch* touch, Event* event){
	//Check if touch was valid
	if(ball_grid->isFirstRowSelected(touch)){
		ball_grid->setChosenPath(ball_grid->_chosen_idx);
		ball_grid->setBurstBalls(ball_grid->_chosen_idx);
		ball_grid->highlightPath();
		return true;
	}

	return false;
}

// Handles the manipulation of grid elements (adding and removing balls)
void Game::onTouchEnded(Touch* touch, Event* event){
	// Check if the user is still on the first row otherwise cancel his choice
	if (ball_grid->isFirstRowSelected(touch)){

		// Animate the balls and manipulate the grid
		ball_grid->generateNewGrid();
		ball_grid->highlightPath();

		// Add the new balls to the scene graph
		for (auto ball : ball_grid->balls_to_be_added){
			this->addChild(ball, 1);
		}
		
		//reset opacity
		for ( auto ball_row : ball_grid->ball_sprites ){
			for (auto ball : ball_row){
				ball->setOpacity(255);
			}
		}
	}
	else{
		//Reset opacity
		for ( auto ball_row : ball_grid->ball_sprites ){
			for (auto ball : ball_row){
				ball->setOpacity(255);
			}
		}
	}
}

