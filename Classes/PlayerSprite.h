#pragma once
#include "cocos2d.h"

USING_NS_CC;

class PlayerSprite : public Sprite{
	public:
		CC_SYNTHESIZE(Vec2, _next_position, NextPosition);
		CC_SYNTHESIZE(Vec2, _vector, Vector);
		CC_SYNTHESIZE(Touch*, _touch, Touch);
		PlayerSprite();
		virtual ~PlayerSprite();
		static PlayerSprite* gameSpriteWithFile(const char* file_name);
		virtual void setPosition(const Vec2& position) override;
		float radius();
		
};
