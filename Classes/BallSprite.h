#pragma once
#include "cocos2d.h"

USING_NS_CC;

enum class Color{
	BLUE,
	YELLOW,
	PURPLE,
	ORANGE
};

class BallSprite : public Sprite{
	public:
		CC_SYNTHESIZE(Touch*, _touch, Touch);
		BallSprite();
		virtual ~BallSprite();
		static BallSprite* gameSpriteWithFile(const char* file_name);
		static BallSprite* generateRandomSprite();
		float radius();
		Color color;
		int id;
		static const std::vector<std::string> sprite_paths;
};
