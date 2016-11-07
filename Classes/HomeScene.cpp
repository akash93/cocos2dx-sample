#include "HomeScene.h"
#include "GameScene.h"

USING_NS_CC;

HomeScreen::HomeScreen(void){}
HomeScreen::~HomeScreen(void){}


Scene* HomeScreen::createScene(){
	auto scene = Scene::create();

	auto layer = HomeScreen::create();

	scene->addChild(layer);

	return scene;
}

bool HomeScreen::init(){
	if(!Layer::init()){
		return false;
	}
	
	_screen_size = Director::getInstance()->getVisibleSize();

	initMenu();
	return true;
}

void HomeScreen::initMenu(){
	
	auto start_label = Label::createWithTTF("Start Game", "fonts/Marker Felt.ttf",92);
	auto score_label = Label::createWithTTF("High Scores", "fonts/Marker Felt.ttf",92);
	auto quit_label = Label::createWithTTF("Quit","fonts/Marker Felt.ttf", 92);
	start_game = MenuItemLabel::create(start_label, CC_CALLBACK_1(HomeScreen::startGameCallback, this));
	high_scores = MenuItemLabel::create(score_label, CC_CALLBACK_1(HomeScreen::scoreCallback, this));
	quit_game = MenuItemLabel::create(quit_label, CC_CALLBACK_1(HomeScreen::gameQuitCallback, this));
	
	start_game->setPosition(Point(_screen_size.width / 2, (_screen_size.height / 4) * 3));
	high_scores->setPosition(Point(_screen_size.width / 2, (_screen_size.height / 4) * 2));
	quit_game->setPosition(Point(_screen_size.width / 2, (_screen_size.height / 4) * 1));

	auto *menu = Menu::create(start_game, high_scores, quit_game, NULL);
	menu->setPosition(Point(0,0));
	
	this->addChild(menu);

}

void HomeScreen::startGameCallback(Ref* sender){
	Director::getInstance()->replaceScene(TransitionFade::create(1, Game::createScene()));
}

void HomeScreen::scoreCallback(Ref* sender){

}

void HomeScreen::gameQuitCallback(Ref* sender){
	Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
