#include "BallSprite.h"

BallSprite::BallSprite(void){}

BallSprite::~BallSprite(void){}

// Ball Sprite files
const std::vector<std::string> BallSprite::sprite_paths = {"blue_ball.png", "yellow_ball.png", "purple_ball.png", "orange_ball.png"};

// Generate a sprite object from a given file. Looks in the Resources folder by default
BallSprite* BallSprite::gameSpriteWithFile(const char* filename){
	auto sprite = new BallSprite();
	if (sprite && sprite->initWithFile(filename)){
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return sprite = nullptr;
}

// Helper function to generate a sprite with a random class
BallSprite* BallSprite::generateRandomSprite(){
	int rand_color_idx = std::rand() % sprite_paths.size();
	BallSprite* ball = gameSpriteWithFile(sprite_paths.at(rand_color_idx).c_str());
	ball->color = static_cast<Color>(rand_color_idx);
	ball->setScale(8);
	return ball;
}

// Calculates the radius to help calculate the positioning of the sprite
float BallSprite::radius(){
	return getTexture()->getContentSize().width * 0.5f;
}
