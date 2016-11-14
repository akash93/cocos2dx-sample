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
		std::vector<std::vector<BallSprite*>> ball_sprites; // Contains the sprites making up the grid
		int _num_cols; // Number of columns in the grid
		int _num_rows; // Number of rows in the grid
		int _chosen_idx; // Id of the chosen ball. Member variable so that it can be 
		float _grid_height; // Height of the grid
		float _grid_width; // Width of the grid
		float _grid_step_x; // The x distance between two consecutive balls of the same row
		float _grid_step_y; // The y distance between two consecutive balls of the same column
		cocos2d::Point _grid_origin; // Coordinates of the left bottom ball. Acts as reference point to place balls
		std::vector<int> chosen_path; // Contains the ids of the balls forming the chosen path
		std::vector<int> burst_balls; // Contains the ids of the balls forming the burst balls
		std::vector<BallSprite*> balls_to_be_added; // Stores the new sprites which need to be added to the scene graph
		bool isFirstRowSelected(Touch* touch);
		void generateGrid(int num_cols, int num_rows); 
		void resumeGrid(int num_cols, int num_rows);
		void setChosenPath(int chosen_idx);
		void setBurstBalls(int chosen_idx);
		void highlightPath();
		void addBall(int row_idx, int col_idx);
		void removeBall(int row_idx, int col_idx);
		void generateNewGrid();
		void saveState();
		std::vector<int> getCurrentState();
};
