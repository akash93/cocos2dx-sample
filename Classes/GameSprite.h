#pragma once
#include "cocos2d.h"

USING_NS_CC;

class GameSprite : public Sprite{
	public:
		CC_SYNTHESIZE(Vec2, _next_position, NextPosition);
		CC_SYNTHESIZE(Vec2, _vector, Vector);
		CC_SYNTHESIZE(Touch*, _touch, Touch);
		GameSprite();
		virtual ~GameSprite();
		static GameSprite* gameSpriteWithFile(const char* fileName);
		virtual void setPosition(const Vec2& position) override;
		
};
