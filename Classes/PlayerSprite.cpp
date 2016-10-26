#include "PlayerSprite.h"

PlayerSprite::PlayerSprite(void){
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

float PlayerSprite::radius(){
	return getTexture()->getContentSize().width * 0.5f;
}
