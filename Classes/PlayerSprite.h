#pragma once
#include "cocos2d.h"
#include "GameSprite.h"

USING_NS_CC;

enum class PlayerClass{
	RED,
	GREEN,
	BLUE,
	YELLOW
};

class PlayerSprite: public GameSprite{
	public:
		PlayerSprite();
		virtual ~PlayerSprite();
		PlayerClass pClass;
		int score;

};
