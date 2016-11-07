#pragma once
#include "cocos2d.h"
#include "BallSprite.h"

#define SCALE_DURATION 0.2f
#define MOVE_DURATION 0.2f
#define DELAY_DURATION 0.2f

class BallGrid{
	public:
		BallGrid();
		virtual ~BallGrid();
		std::vector<std::vector<BallSprite*>> ball_sprites;
		void generateGrid(int num_cols, int num_rows);
		void resumeGrid(int num_cols, int num_rows);
		int _num_cols;
		int _num_rows;
		int _chosen_idx;
		float _grid_height;
		float _grid_width;
		float _grid_step_x;
		float _grid_step_y;
		cocos2d::Point _grid_origin;
		std::vector<int> chosen_path;
		std::vector<int> burst_balls;
		std::vector<BallSprite*> balls_to_be_added;
		void setPath(int chosen_idx);
		void highlightPath();
		int getScore(Color player_class, Color enemy_class, int base_attack, int base_burst_damage);
		void moveBallsDown(int start_row_idx, int col_idx, int step_size);
		void addBall(int row_idx, int col_idx);
		void removeBall(int row_idx, int col_idx);
		void generateNewGrid();
		void saveState();
		std::vector<int> getCurrentState();
};
