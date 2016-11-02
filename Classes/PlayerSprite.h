#pragma once
#include "cocos2d.h"

USING_NS_CC;

class PlayerSprite : public Sprite{
	public:
		CC_SYNTHESIZE(Touch*, _touch, Touch);
		PlayerSprite();
		virtual ~PlayerSprite();
		static PlayerSprite* gameSpriteWithFile(const char* file_name);
		float radius();
};
