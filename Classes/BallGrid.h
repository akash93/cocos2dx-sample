#pragma once
#include "cocos2d.h"
#include "BallSprite.h"

class BallGrid{
	public:
		BallGrid();
		virtual ~BallGrid();
		std::vector<std::vector<BallSprite*>> ball_sprites;
		void generateGrid(int num_cols, int num_rows, std::vector<std::string> sprite_names);
		int _num_cols;
		int _num_rows;
		std::vector<int> chosen_path;
		std::vector<int> burst_balls;
		void setPath(int chosen_idx);
		int getScore(Color player_class, Color enemy_class, int base_attack, int base_burst_damage);
		void generateNewGrid(std::vector<int> ball_path);
};
