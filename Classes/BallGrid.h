#pragma once
#include "cocos2d.h"
#include "BallSprite.h"

class BallGrid{
	public:
		BallGrid();
		virtual ~BallGrid();
		std::vector<std::vector<BallSprite*>> ball_sprites;
		void generateGrid(int num_cols, int num_rows);
		int _num_cols;
		int _num_rows;
		std::vector<int> chosen_path;
		std::vector<int> burst_balls;
		std::vector<BallSprite*> balls_to_be_added;
		std::vector<BallSprite*> balls_to_be_removed;
		void setPath(int chosen_idx);
		int getScore(Color player_class, Color enemy_class, int base_attack, int base_burst_damage);
		void generateNewGrid();
};
