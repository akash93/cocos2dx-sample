#include "BallGrid.h"

BallGrid::BallGrid(void){}

BallGrid::~BallGrid(void){}

// Generate a grid.
// @param num_rows: Number of rows in the grid
// @param num_cols: Number of columns in the grid
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

// Loads a previously saved configuration. 
// @param num_rows: Number of rows in the grid
// @param num_cols: Number of columns in the grid
// @param ball_classes: Vector containing the classes of every ball in the saved config
void BallGrid::resumeGrid(int num_cols, int num_rows){
	_num_cols = num_cols;
	_num_rows = num_rows;
	std::vector<int> ball_classes = getCurrentState();
	int ball_idx = 1;
	for (int i = 0; i < num_rows; i++) {
		std::vector<BallSprite*> rows;
		for (int j = 0; j < num_cols; j++) {
			int color_idx = ball_classes[ball_idx - 1];
			BallSprite* ball_sprite = BallSprite::gameSpriteWithFile(BallSprite::sprite_paths[color_idx]);
			ball_sprite->id = ball_idx;
			ball_sprite->color = static_cast<Color>(color_idx);
			rows.push_back(ball_sprite);
			ball_idx++;
		}
		ball_sprites.push_back(rows);
	}
}

// Fill up the chosen path and burst ball vectors based on the chosen column
// @param chosen_idx: The id of the chosen element
// Since id starts from 1 the col index for current element will be chosen_id - 1
void BallGrid::setPath(int chosen_idx){
	//Clear the chosen and burst ball vectors from the previous state
	chosen_path.clear();
	burst_balls.clear();
		// Get the color of the chosen ball and find the longest path with the given color
	// and add it to chosen path
	Color chosen_color = ball_sprites[0][chosen_idx - 1]->color;
	getChosenPath(chosen_idx, chosen_color);

}


// Generate the list of chosen and burst balls
// @param chosen_idx : The id of the chosen ball
// @param chosem_color : The color of the chosen ball
void BallGrid::getChosenPath(int chosen_idx, Color chosen_color){
	
	std::vector<std::vector<int>> longest_lengths;

	//Initialize length matrix
	for (int i = 0; i < _num_rows; i++){
		std::vector<int> rows;
		for (int j = 0; j < _num_cols; j++){
			// we are only going to work with balls of the chosen color so set the others to invalid (-1) values
			if (ball_sprites[i][j]->color == chosen_color){
				rows.push_back(1);
			}
			else{
				rows.push_back(-1);
			}
		}
		longest_lengths.push_back(rows);
	}

	// For each ball check the top and top right neighbor
	// If they are of the same color then we can add the longest path length
	// for that ball to the current ball
	for (int row_idx = _num_rows - 1; row_idx >= 0; row_idx--){
		for (int col_idx = 0; col_idx < _num_cols; col_idx++){
			if (ball_sprites[row_idx][col_idx]->color == chosen_color){
				int a  = 0, b = 0;
				if (row_idx + 1 < _num_rows && ball_sprites[row_idx + 1][col_idx]->color == chosen_color){
					a = longest_lengths[row_idx + 1][col_idx];
				}
				if (row_idx + 1 < _num_rows && col_idx + 1 < _num_cols && ball_sprites[row_idx + 1][col_idx + 1]->color == chosen_color){
					b = longest_lengths[row_idx + 1][col_idx + 1];
				}
				longest_lengths[row_idx][col_idx] = 1 + std::max(a, b);
			}
		}
	}

	// Use the longest path length matrix to calculate the longest 
	// path from the chosen index
	chosen_path.push_back(chosen_idx);
	int path_length = longest_lengths[0][chosen_idx - 1];
	int curr_col = chosen_idx - 1;
	for (int i = 0; i < _num_rows - 1 && path_length > 0; i++){
		if (longest_lengths[i + 1][curr_col] == path_length - 1){
			int ball_id = (i + 1) * _num_cols + curr_col + 1;
			chosen_path.push_back(ball_id);
		}
		else if (curr_col + 1 < _num_cols && longest_lengths[i + 1][curr_col + 1] == path_length - 1){
			int ball_id = (i + 1) * _num_cols + curr_col + 2;
			chosen_path.push_back(ball_id);
			curr_col +=1;
		}
		path_length -= 1;
	}
	
	// Find the burst balls corresponding the longest path
	for (int ball_id : chosen_path){
		int row_idx = (ball_id - 1) / _num_cols;
		int col_idx = (ball_id - 1) % _num_cols;
		
		//Check left
		if (col_idx != 0 && ball_sprites[row_idx][col_idx - 1]->color == chosen_color){
			int burst_ball_id = row_idx * _num_cols + col_idx;
			burst_balls.push_back(burst_ball_id);
		}

		//Check right
		if (col_idx != _num_cols - 1 && ball_sprites[row_idx][col_idx + 1]->color == chosen_color){
			int burst_ball_id = row_idx * _num_cols + col_idx + 2;
			burst_balls.push_back(burst_ball_id);
		}
	}

}

// Higlight the chosen path and burst balls for a given choice
void BallGrid::highlightPath(){

	for (int row_idx = 0; row_idx < _num_rows; row_idx++){
		for (int col_idx = 0; col_idx < _num_cols; col_idx++){
			int ball_id = row_idx * _num_cols + col_idx + 1;
			bool is_chosen = std::find(chosen_path.begin(), chosen_path.end(), ball_id) != chosen_path.end();
			bool is_burst = std::find(burst_balls.begin(), burst_balls.end(), ball_id) != burst_balls.end();
			if (is_chosen || is_burst){
				ball_sprites[row_idx][col_idx]->setOpacity(255);
			}else{
				ball_sprites[row_idx][col_idx]->setOpacity(128);
			}
		}
	}

}

// Calculate the score based on the player and enemy stats
// @param player_class, @param enemy_class decide the damage multipliers
// @param base_attack: Damage for each ball in the chosen path
// @param base_burst_damage: Damage for each ball in burst balls
// @return : The score of the current move based on above params
int BallGrid::getScore(Color player_class, Color enemy_class, int base_attack, int base_burst_damage){
	// TODO add real class based damage like in DBZ game
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

// Add a ball at the given location on the grid
// @param row_idx, @param col_idx define the location where the 
// ball needs to be added
void BallGrid::addBall(int row_idx, int col_idx){
	BallSprite* new_ball = BallSprite::generateRandomSprite();
	auto new_x = _grid_origin.x + col_idx * _grid_step_x;
	auto new_y = _grid_origin.y + row_idx * _grid_step_y;
	new_ball->id = row_idx * _num_cols + col_idx + 1;
	new_ball->setPosition(cocos2d::Vec2(new_x, new_y));
	new_ball->setScale(0.0f);
	ball_sprites[row_idx][col_idx] = new_ball;
	balls_to_be_added.push_back(new_ball);
	auto delay_action = cocos2d::DelayTime::create(DELAY_DURATION);
	auto scale_action = cocos2d::ScaleTo::create(SCALE_DURATION, 1.0f);
	auto appear_seq = cocos2d::Sequence::create(delay_action, scale_action, nullptr);
	new_ball->runAction(appear_seq);

}

// Remove a particular ball from the grid
// @param row_idx, @param col_idx define which ball in the grid needs to be removed
// scales the ball down to zero and then calls RemoveSelf to remove it from the scene graph
void BallGrid::removeBall(int row_idx, int col_idx){
	auto scale_action = cocos2d::ScaleTo::create(SCALE_DURATION, 0.0f);
	auto remove_action = cocos2d::RemoveSelf::create();
	auto seq = cocos2d::Sequence::create(scale_action, remove_action, nullptr);
	BallSprite* removed_ball = ball_sprites[row_idx][col_idx];
	removed_ball->runAction(seq);
}

// Performs the grid manipulation once chosen_path and burst_balls are fixed.
void BallGrid::generateNewGrid(){

	//Clear the vectors from the previous turn
	balls_to_be_added.clear();
	removed_balls.clear();

	//All chosen and burst balls need to be removed.
	std::vector<int> balls_to_be_removed = chosen_path;
	balls_to_be_removed.insert(balls_to_be_removed.end(), burst_balls.begin(), burst_balls.end());
	//Sort is called to ensure that the balls in the list are in geometric order
	std::sort(balls_to_be_removed.begin(), balls_to_be_removed.end());

	for (int ball_id : balls_to_be_removed){
		int row_idx = (ball_id - 1) / _num_cols;
		int col_idx = (ball_id - 1) % _num_cols;
		removeBall(row_idx, col_idx);
	}

	// Create a 2d vector/deque for the removed balls by separating them column wise.
	// Each row is a deque so that first element can be removed easily.
	std::vector<std::deque<int>> remove_balls;
	for (int i = 0; i < _num_cols; i++){
		std::deque<int> cols = {};
		remove_balls.push_back(cols);
	}
	for (int ball_id : balls_to_be_removed){
		int col_idx = (ball_id - 1) % _num_cols;
		remove_balls[col_idx].push_back(ball_id);
	}

	// For each column move the column balls to the position of the balls being removed
	for (int col_idx = 0; col_idx < _num_cols; col_idx++){
		std::deque<int> col_balls_remove = remove_balls[col_idx];
		std::deque<int> movable_balls;
		if (col_balls_remove.size() != 0){
			//find which balls can be moved in the current column
			int start_row_idx = (col_balls_remove[0] - 1) / _num_cols;
			for (int row_idx = start_row_idx; row_idx < _num_rows; row_idx++){
				int ball_id = row_idx * _num_cols + col_idx + 1;
				if (std::find(col_balls_remove.begin(), col_balls_remove.end(),ball_id) == col_balls_remove.end()){
					movable_balls.push_back(ball_id);
				}
			}
			
			// Move the movable balls to their final positons
			for (int movable_ball_id : movable_balls){
				int swap_from_row_idx =  (movable_ball_id - 1) / _num_cols;
				int swap_to_row_idx = (col_balls_remove[0] - 1) / _num_cols;
				auto move_to_x = _grid_origin.x + (col_idx * _grid_step_x);
				auto move_to_y = _grid_origin.y + (swap_to_row_idx * _grid_step_y);
				BallSprite* moving_ball = ball_sprites[swap_from_row_idx][col_idx];
				auto move_action = cocos2d::MoveTo::create(MOVE_DURATION, cocos2d::Vec2(move_to_x, move_to_y));
				auto delay_action = cocos2d::DelayTime::create(DELAY_DURATION);
				auto seq = cocos2d::Sequence::create(delay_action, move_action, nullptr);
				moving_ball->runAction(seq);
				moving_ball->id = swap_to_row_idx * _num_cols + col_idx + 1;
				ball_sprites[swap_to_row_idx][col_idx] = moving_ball;
				col_balls_remove.pop_front();
				col_balls_remove.push_back(movable_ball_id);
				std::sort(col_balls_remove.begin(), col_balls_remove.end());
				movable_balls.pop_front();
			}

			// Only case that remains is that there are still some empty spaces left on the grid but above process
			// ensures that they will all be at the top of the column
			int num_balls_to_be_added = col_balls_remove.size();
			for (int row_idx = _num_rows - num_balls_to_be_added; row_idx < _num_rows; row_idx++){
				addBall(row_idx, col_idx);
			}
		}
	}
	// Save the progess
	saveState();

}


//Saves the current state of the grid (classes of all balls) to a plist file.
void BallGrid::saveState(){
	std::string writable_path = cocos2d::FileUtils::getInstance()->getWritablePath();
	std::string full_path = writable_path + "save.plist";
	cocos2d::ValueVector ball_classes;
	for (int row_idx = 0; row_idx < _num_rows; row_idx++){
		for (int col_idx = 0; col_idx < _num_cols; col_idx++){\
			int ball_color = static_cast<int> (ball_sprites[row_idx][col_idx]->color);
			ball_classes.push_back(cocos2d::Value(ball_color));
		}
	}
	cocos2d::FileUtils::getInstance()->writeValueVectorToFile(ball_classes, full_path.c_str());
	cocos2d::UserDefault::getInstance()->setBoolForKey("save_exists", true);
}


// Retrieve the current state from a saved file. 
// @returns vector containing classes of the balls in the grid
std::vector<int> BallGrid::getCurrentState(){
    std::string writable_path = cocos2d::FileUtils::getInstance()->getWritablePath();
	std::string full_path = writable_path + "save.plist";
	cocos2d::ValueVector class_values = cocos2d::FileUtils::getInstance()->getValueVectorFromFile(full_path.c_str());
	std::vector<int> ball_classes;
	for (int i = 0 ; i < class_values.size(); i++){
		ball_classes.push_back(class_values[i].asInt());
	}

    return ball_classes;
}
