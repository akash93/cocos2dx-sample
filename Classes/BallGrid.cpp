#include "BallGrid.h"

BallGrid::BallGrid(void){}

BallGrid::~BallGrid(void){}

//Generate a grid based on the sprite paths provided
void BallGrid::generateGrid(int num_cols, int num_rows){
	_num_cols = num_cols;
	_num_rows = num_rows;
	int ball_idx = 1;
	for (int i = 0; i < num_rows; i++) {
		std::vector<BallSprite*> rows;
		for (int j = 0; j < num_cols; j++) {
			BallSprite* ball_sprite = BallSprite::generateRandomSprite();
			ball_sprite->id = ball_idx;
			rows.push_back(ball_sprite);
			ball_idx++;
		}
		ball_sprites.push_back(rows);
	}

}

// Set the chosen path and burst ball ids based on chosen index
void BallGrid::setPath(int chosen_idx){
	chosen_path.clear();
	burst_balls.clear();
	if (chosen_idx > _num_cols){
		return; //Invalid selection. Nothing to do
	}
	Color chosen_color = ball_sprites[0][chosen_idx - 1]->color;
	int i = 0;
	while (i < _num_rows && ball_sprites[i][chosen_idx - 1]->color == chosen_color){
		chosen_path.push_back(ball_sprites[i][chosen_idx - 1]->id);
		i++;
	}
	
	for (int j = 0; j < chosen_path.size(); j++){
		if (chosen_idx == 1){
			if (ball_sprites[j][chosen_idx]->color == chosen_color){
				burst_balls.push_back(ball_sprites[j][chosen_idx]->id);
			}
		}

		else if (chosen_idx == _num_cols){
			if (ball_sprites[j][chosen_idx - 2]->color == chosen_color){
				burst_balls.push_back(ball_sprites[j][chosen_idx - 2]->id);
			}
		}
		else{
			if (ball_sprites[j][chosen_idx - 2]->color == chosen_color){
				burst_balls.push_back(ball_sprites[j][chosen_idx - 2]->id);
			}

			if (ball_sprites[j][chosen_idx]->color == chosen_color){
				burst_balls.push_back(ball_sprites[j][chosen_idx]->id);
			}
		}

	}


}


int BallGrid::getScore(Color player_class, Color enemy_class, int base_attack, int base_burst_damage){
	int damage_multiplier = 1;
	Color chosen_color = ball_sprites[0][chosen_path[0] - 1]->color;
	if (chosen_color == player_class){
		damage_multiplier *= 2;
	}

	if (chosen_color == enemy_class){
		damage_multiplier /= 2;
	}

	int score = (base_attack * chosen_path.size() + base_burst_damage * burst_balls.size()) * damage_multiplier;

	return score;
}

void BallGrid::moveBallsDown(int start_row_idx, int col_idx, int step_size){
	for(int swap_from_row_idx = start_row_idx; swap_from_row_idx < _num_rows; swap_from_row_idx++){
		int swap_to_row_idx = swap_from_row_idx - step_size;
		BallSprite* swap_from = ball_sprites[swap_from_row_idx][col_idx];
		BallSprite* swap_to = ball_sprites[swap_to_row_idx][col_idx];
		auto move_action = cocos2d::MoveTo::create(MOVE_DURATION, swap_to->getPosition());
		swap_from->runAction(move_action);
		swap_from->id = swap_to_row_idx * _num_cols + col_idx + 1;
		ball_sprites[swap_to_row_idx][col_idx] = swap_from;
	}
}

void BallGrid::removeBall(int row_idx, int col_idx){
	auto fade_action = cocos2d::FadeOut::create(FADE_DURATION);
	BallSprite* removed_ball = ball_sprites[row_idx][col_idx];
	removed_ball->runAction(fade_action);
	balls_to_be_removed.push_back(removed_ball);
}

void BallGrid::generateNewGrid(){
	balls_to_be_added.clear();
	balls_to_be_removed.clear();
	int num_balls = _num_rows * _num_cols;
    int num_balls_to_be_added = chosen_path.size();
	int chosen_col_idx = (chosen_path[0] - 1) % _num_cols;
	
	//Remove chosen balls
	for (int row_idx = 0; row_idx < chosen_path.size(); row_idx++){
		removeBall(row_idx, chosen_col_idx);
	}

	//Move balls in the chosen column down
	moveBallsDown(num_balls_to_be_added, chosen_col_idx, chosen_path.size());
	
	//Add new balls in the chosen column
	for (int new_row_idx = _num_rows - num_balls_to_be_added; new_row_idx < _num_rows; new_row_idx++){
		BallSprite* new_ball = BallSprite::generateRandomSprite();
		BallSprite* old_ball = ball_sprites[new_row_idx][chosen_col_idx];
        new_ball->id = new_row_idx * _num_cols + chosen_col_idx + 1;
		new_ball->setPosition(old_ball->getPosition());
		ball_sprites[new_row_idx][chosen_col_idx] = new_ball;
		balls_to_be_added.push_back(new_ball);
	}

	// For each burst ball: fade the ball and move all balls above it down
	for (int burst_ball_id : burst_balls ){
		int burst_ball_col_idx = (burst_ball_id - 1) % _num_cols;
		int burst_ball_row_idx = (burst_ball_id - 1) / _num_cols;
		
		//fade the ball
		removeBall(burst_ball_row_idx, burst_ball_col_idx);
		//Move balls down
		moveBallsDown(burst_ball_row_idx + 1, burst_ball_col_idx, 1);

		auto final_x = ball_sprites[0][burst_ball_col_idx]->getPositionX();
		auto final_y = ball_sprites[_num_rows - 1][0]->getPositionY();
		//Add a ball to the top
		BallSprite* new_ball = BallSprite::generateRandomSprite();
		int new_row_idx = _num_rows - 1; //Add to last row
		new_ball->id = new_row_idx * _num_cols + burst_ball_col_idx + 1;
		new_ball->setPosition(cocos2d::Vec2(final_x, final_y));
		ball_sprites[new_row_idx][burst_ball_col_idx] = new_ball;
		balls_to_be_added.push_back(new_ball);
	}

}
