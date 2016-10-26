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
		CC_SYNTHESIZE(Vec2, _next_position, NextPostion);
		CC_SYNTHESIZE(Vec2, _vector, Vector);
		CC_SYNTHESIZE(Touch*, _touch, Touch);
		BallSprite();
		virtual ~BallSprite();
		static BallSprite* gameSpriteWithFile(const char* file_name);
		virtual void setPosition(const Vec2& position) override;
		float radius();
		Color color;
};
