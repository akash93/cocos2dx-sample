#include "BallSprite.h"

BallSprite::BallSprite(void){}

BallSprite::~BallSprite(void){}

const std::vector<std::string> BallSprite::sprite_paths = {"blue_ball.png", "yellow_ball.png", "purple_ball.png", "orange_ball.png"};

BallSprite* BallSprite::gameSpriteWithFile(const char* filename){
	auto sprite = new BallSprite();
	if (sprite && sprite->initWithFile(filename)){
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return sprite = nullptr;
}

float BallSprite::radius(){
	return getTexture()->getContentSize().width * 0.5f;
}
