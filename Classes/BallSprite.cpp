#include "BallSprite.h"

BallSprite::BallSprite(void){
}

BallSprite::~BallSprite(void){

}

BallSprite* BallSprite::gameSpriteWithFile(const char* filename){
	auto sprite = new BallSprite();
	if(sprite && sprite->initWithFile(filename)){
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return sprite = nullptr;
}

float BallSprite::radius(){
	return getTexture()->getContentSize().width * 0.5f;
}
