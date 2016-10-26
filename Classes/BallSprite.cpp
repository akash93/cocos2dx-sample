#include "BallSprite.h"

BallSprite::BallSprite(void){
	_vector = Vec2(0,0);
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

void BallSprite::setPosition(const Point& pos){
	Sprite::setPosition(pos);
	if(!_next_position.equals(pos)){
		_next_position = pos;
	}
}

float BallSprite::radius(){
	return getTexture()->getContentSize().width * 0.5f;
}
