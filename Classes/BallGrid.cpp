#include "BallGrid.h"

BallGrid::BallGrid(void){}

BallGrid::~BallGrid(void){}


//Generate a grid based on the sprite paths provided
void BallGrid::generateGrid(int num_cols, int num_rows, std::vector<std::string> sprite_names){
	_num_cols = num_cols;
	_num_rows = num_rows;
	std::srand(std::time(0));
	int ball_idx = 1;
	for (int i = 0; i< num_rows; i++) {
		std::vector<BallSprite*> rows;
		for (int j = 0; j< num_cols; j++) {
			int rand_sprite_idx = std::rand() % sprite_names.size();
			BallSprite* ball_sprite = BallSprite::gameSpriteWithFile(sprite_names.at(rand_sprite_idx).c_str());
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
    chosen_path = {};
    burst_balls = {};
	if(chosen_idx > _num_cols){
		return; //Invalid selection. Nothing to do
	}
	Color chosen_color = ball_sprites[0][chosen_idx-1]->color;
	int i = 0;
	while(i < _num_rows && ball_sprites[i][chosen_idx-1]->color == chosen_color){
		chosen_path.push_back(ball_sprites[i][chosen_idx-1]->id);
		i++;
	}
	
	for (int j = 0; j < chosen_path.size(); j++){
		if(chosen_idx == 1){
			if(ball_sprites[j][chosen_idx]->color == chosen_color){
				burst_balls.push_back(ball_sprites[j][chosen_idx]->id);
			}
			continue;
		}

		else if(chosen_idx == _num_cols){
			if(ball_sprites[j][chosen_idx - 2] -> color == chosen_color){
				burst_balls.push_back(ball_sprites[j][chosen_idx - 2]->id);
			}
			continue;
		}
		else{
			if(ball_sprites[j][chosen_idx - 2] -> color == chosen_color){
				burst_balls.push_back(ball_sprites[j][chosen_idx - 2]->id);
			}

			if(ball_sprites[j][chosen_idx] -> color == chosen_color){
				burst_balls.push_back(ball_sprites[j][chosen_idx]->id);
			}
		}

	}

	//TODO add animations for chosen and burst balls

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

