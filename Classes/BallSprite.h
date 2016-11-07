#pragma once
#include "cocos2d.h"

USING_NS_CC;

#define NUM_CLASSES 5
#define NUM_SPRITES_PER_CLASS 2

enum class Color{
	BLUE,
	GREEN,
	PURPLE,
	ORANGE,
	RED
};

class BallSprite : public Sprite{
	public:
		CC_SYNTHESIZE(Touch*, _touch, Touch);
		BallSprite();
		virtual ~BallSprite();
		static BallSprite* gameSpriteWithFile(std::string file_name);
		static BallSprite* generateRandomSprite();
		float radius();
		Color color;
		int id;
		const static std::string sprite_paths[]; 
		static Vector<SpriteFrame*> setupAnimation(const char* format);

};
