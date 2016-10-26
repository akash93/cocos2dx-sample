#include "PlayerSprite.h"

PlayerSprite::PlayerSprite(void){
	_vector = Vec2(0,0);
}

PlayerSprite::~PlayerSprite(void){

}

PlayerSprite* PlayerSprite::gameSpriteWithFile(const char* filename){
	auto sprite = new PlayerSprite();
	if(sprite && sprite->initWithFile(filename)){
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return sprite = nullptr;
}

void PlayerSprite::setPosition(const Point& pos){
	Sprite::setPosition(pos);
	if(!_next_position.equals(pos)){
		_next_position = pos;
	}
}

float PlayerSprite::radius(){
	return getTexture()->getContentSize().width * 0.5f;
}
