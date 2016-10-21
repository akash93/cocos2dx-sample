#include "GameSprite.h"

GameSprite::GameSprite(void){
	_vector = Vec2(0,0);
}

GameSprite::~GameSprite(void){

}

GameSprite* GameSprite::gameSpriteWithFile(const char* filename){
	auto sprite = new GameSprite();
	if(sprite && sprite->initWithFile(filename)){
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return sprite = nullptr;
}

void GameSprite::setPosition(const Point& pos){
	Sprite::setPosition(pos);
	if(!_next_position.equals(pos)){
		_next_position = pos;
	}
}
