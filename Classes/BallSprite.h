#pragma once
#include "cocos2d.h"

USING_NS_CC;

enum class Color{
	RED,
	BLUE,
	GREEN,
	YELLOW,
	ORANGE,
	PURPLE
};

class BallSprite : public Sprite{
	public:
		CC_SYNTHESIZE(Touch*, _touch, Touch);
		BallSprite();
		virtual ~BallSprite();
		static BallSprite* gameSpriteWithFile(const char* file_name);
		float radius();
		Color color;
		int id;
};
