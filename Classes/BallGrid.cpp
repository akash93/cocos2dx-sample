#include "BallGrid.h"

BallGrid::BallGrid(void){}

BallGrid::~BallGrid(void){}

//Generate a grid based on the sprite paths provided
void BallGrid::generateGrid(int num_cols, int num_rows){
	_num_cols = num_cols;
	_num_rows = num_rows;
	std::srand(std::time(0));
	int ball_idx = 1;
	for (int i = 0; i < num_rows; i++) {
		std::vector<BallSprite*> rows;
		for (int j = 0; j < num_cols; j++) {
			int rand_sprite_idx = std::rand() % BallSprite::sprite_paths.size();
			BallSprite* ball_sprite = BallSprite::gameSpriteWithFile(BallSprite::sprite_paths.at(rand_sprite_idx).c_str());
			ball_sprite->color = static_cast<Color>(rand_sprite_idx);
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

void BallGrid::generateNewGrid(){
	/*
	 * Swap chosen path
	*/
	balls_to_be_added.clear();
	balls_to_be_removed.clear();
	int num_balls = _num_rows * _num_cols;
    int num_balls_to_be_added = chosen_path.size();
	int chosen_col_idx = (chosen_path[0] - 1) % _num_cols;
	
	//Remove chosen balls
	for (int row_idx = 0; row_idx < chosen_path.size(); row_idx++){
		auto fade_action = cocos2d::FadeOut::create(0.5f);
		BallSprite* removed_ball = ball_sprites[row_idx][chosen_col_idx];
		removed_ball->runAction(fade_action);
		balls_to_be_removed.push_back(removed_ball);
	}

	//Move balls in the chosen column down
	for (int swap_from_row_idx = num_balls_to_be_added; swap_from_row_idx < _num_rows; swap_from_row_idx++){
		int swap_to_row_idx = swap_from_row_idx - chosen_path.size();
		BallSprite* swap_from = ball_sprites[swap_from_row_idx][chosen_col_idx];
		BallSprite* swap_to = ball_sprites[swap_to_row_idx][chosen_col_idx];
		auto move_to = cocos2d::MoveTo::create(0.5f, swap_to->getPosition());
		swap_from->runAction(move_to);
		swap_from->id = swap_to_row_idx * _num_cols + chosen_col_idx + 1;
		ball_sprites[swap_to_row_idx][chosen_col_idx] = swap_from;
	}

	//Add new balls in the chosen column
	for (int new_row_idx = _num_rows - num_balls_to_be_added; new_row_idx < _num_rows; new_row_idx++){
		int rand_color = std::rand() % BallSprite::sprite_paths.size();
		BallSprite* new_ball = BallSprite::gameSpriteWithFile(BallSprite::sprite_paths.at(rand_color).c_str());
		new_ball->color = static_cast<Color>(rand_color);
		BallSprite* old_ball = ball_sprites[new_row_idx][chosen_col_idx];
        new_ball->id = new_row_idx * _num_cols + chosen_col_idx + 1;
		new_ball->setPosition(old_ball->getPosition());
		new_ball->setScale(8);
		ball_sprites[new_row_idx][chosen_col_idx] = new_ball;
		balls_to_be_added.push_back(new_ball);
	}

	// For each burst ball: fade the ball and move all balls above it down
	for (int burst_ball_id : burst_balls ){
		int burst_ball_col_idx = (burst_ball_id - 1) % _num_cols;
		int burst_ball_row_idx = (burst_ball_id - 1) / _num_cols;
		
		//fade the ball
		auto fade_action = cocos2d::FadeOut::create(0.5f);
		BallSprite* burst_ball = ball_sprites[burst_ball_row_idx][burst_ball_col_idx];
		burst_ball->runAction(fade_action);
		balls_to_be_removed.push_back(burst_ball);
		//Move balls down
		auto move_to_position = burst_ball->getPosition();
		for (int move_from_row_idx = burst_ball_row_idx + 1; move_from_row_idx < _num_rows; move_from_row_idx++){
			BallSprite* moving_ball = ball_sprites[move_from_row_idx][burst_ball_col_idx];
			auto move_action = cocos2d::MoveTo::create(0.5f, move_to_position);
			move_to_position = moving_ball->getPosition();
			moving_ball->runAction(move_action);
			moving_ball->id = (move_from_row_idx - 1) * _num_cols + burst_ball_col_idx + 1;
			ball_sprites[move_from_row_idx - 1][burst_ball_col_idx] = moving_ball;
		}

		//Add a ball to the top
		int rand_color = std::rand() % BallSprite::sprite_paths.size();
		BallSprite* new_ball = BallSprite::gameSpriteWithFile(BallSprite::sprite_paths.at(rand_color).c_str());
		new_ball->color = static_cast<Color>(rand_color);
		int new_row_idx = _num_rows - 1; //Add to last row
		new_ball->id = new_row_idx * _num_cols + burst_ball_col_idx + 1;
		new_ball->setPosition(move_to_position);
		new_ball->setScale(8);
		ball_sprites[new_row_idx][burst_ball_col_idx] = new_ball;
		balls_to_be_added.push_back(new_ball);
	}

}
