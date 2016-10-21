#pragma once
#include "cocos2d.h"
#include "GameSprite.h"

USING_NS_CC;

enum class BallClass{
	RED,
	BLUE,
	GREEN,
	YELLOW
};

class BallSprite : public GameSprite{
	public:
		BallSprite();
		virtual ~BallSprite();
		BallClass bClass;
		float radius();
};
