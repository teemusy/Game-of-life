#include <curses.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>

#include "constants.h"
#include "snake.h"



void Snake::set_head_location (struct cell_info map[ROWS][COLUMNS], int loc_x, int loc_y){
	
	snake_head_var[0] = loc_y;
	snake_head_var[1] = loc_x;
	map[snake_head_var[0]][snake_head_var[1]].current_status = 0;
	map[snake_head_var[0]][snake_head_var[1]].future_status = 0;
	last_dir = random_direction ();
	snake_length = 0;
	snake_alive = 1;
	
	for (i = 0; i < SNAKE_MAX_LEN; i++){
		snake_location[0][i] = 0;
		snake_location[1][i] = 0;
	}
}

void Snake::update_snake (struct cell_info map[ROWS][COLUMNS]){
	move_snake(map);
	
}

void Snake::lay_egg (struct cell_info map[ROWS][COLUMNS], int loc_y, int loc_x){
	
	map[loc_y][loc_x].egg = 1;
	map[loc_y][loc_x].current_status = 0;
	map[loc_y][loc_x].future_status = 0;
	map[loc_y][loc_x].snake_body = 0;
	map[loc_y][loc_x].snake_head = 0;
	
}

void Snake::hatch_egg (struct cell_info map[ROWS][COLUMNS]){
	
	if (hatching_time >= TIME_TO_HATCH){
		set_head_location(map, snake_head_var[1], snake_head_var[0]);
		snake_alive = 1;
		map[snake_head_var[0]][snake_head_var[1]].egg = 0;
		map[snake_head_var[0]][snake_head_var[1]].snake_head = 1;
	}
	
}

void Snake::destroy_snake (struct cell_info map[ROWS][COLUMNS]){
	int i, j;
	for (i = 0; i < ROWS; i++){
		
		for (j = 0; j < COLUMNS; j++){
			if (map[i][j].snake_head || map[i][j].snake_body){
			
				map[i][j].snake_head = 0;
				map[i][j].snake_body = 0;
				map[i][j].current_status = 1;
				map[i][j].future_status = 1;
			}
		}
	}	
}

void Snake::move_snake (struct cell_info map[ROWS][COLUMNS]){
	int direction, legal_direction;
	
	
	if (snake_alive){
		
		snake_old_head_var[0] = snake_head_var[0];
		snake_old_head_var[1] = snake_head_var[1];
		n = 0;
		e = 0;
		s = 0;
		w = 0;
		//check for legal direction
		do{
			
			//destroy snake if snake knots itself
			if (n > 0 && e > 0  && s > 0  && w > 0){
				snake_alive = 0;
				hatching_time = 0;
				destroy_snake (map);
				lay_egg(map, snake_head_var[0], snake_head_var[1]);
			}
			
			direction = random_direction ();
			legal_direction = 1;

			//>75% chance to choose last direction for more natural movement
			//if snake is just hatched it moves more randomly
			if (direction != 8 && snake_length > 0){
				direction = last_dir;
			}
			
			else {
				direction = random_direction ();
			}
			
			switch (direction){
				
				case 2:
					snake_head_var[0]++;
					last_dir = 8;
					s++;
					#ifdef DEBUG_MODE
						std::cout << "South \t";
					#endif
					break;		
				
				case 4:
					snake_head_var[1]--;
					last_dir = 6;
					w++;
					#ifdef DEBUG_MODE
						std::cout << "West \t";
					#endif
					break;		
				
				case 6:
					snake_head_var[1]++;
					last_dir = 4;
					e++;
					#ifdef DEBUG_MODE
						std::cout << "East \t";
					#endif
					break;		
				
				case 8:
					snake_head_var[0]--;
					last_dir = 2;
					n++;
					#ifdef DEBUG_MODE
						std::cout << "North \t";
					#endif
					break;
					
				default:
					#ifdef DEBUG_MODE
						std::cout << "Default \t";
					#endif
					break;
			} 
			
			if (map[snake_head_var[0]][snake_head_var[1]].snake_body == 1){
				
				snake_head_var[0] = snake_old_head_var[0];
				snake_head_var[1] = snake_old_head_var[1];
				legal_direction = 0;			
			}
			
			if(((snake_head_var[1] == COLUMNS && direction == 6) ||
				(snake_head_var[1] < 0 && direction == 4) ||
				(snake_head_var[0] == ROWS && direction == 2) ||
				(snake_head_var[0] < 0 && direction == 8))){
					
					snake_head_var[0] = snake_old_head_var[0];
					snake_head_var[1] = snake_old_head_var[1];
					legal_direction = 0;	
			}

		}
		while(!legal_direction);

		if(map[snake_head_var[0]][snake_head_var[1]].current_status){
			
			map[snake_head_var[0]][snake_head_var[1]].current_status = 0;
			map[snake_head_var[0]][snake_head_var[1]].future_status = 0;
			
			//if there's existing tail
			if (snake_length > 0 && snake_length < SNAKE_MAX_LEN){
				
				map[snake_old_head_var[0]][snake_old_head_var[1]].snake_head = 0;
				map[snake_head_var[0]][snake_head_var[1]].snake_head = 1;	
				map[snake_old_head_var[0]][snake_old_head_var[1]].snake_body = 1;
				map[snake_location[0][snake_length]][snake_location[1][snake_length]].snake_body = 0;
				array_shift(snake_location, SNAKE_MAX_LEN, 1);
				snake_location[0][0] = snake_old_head_var[0];
				snake_location[1][0] = snake_old_head_var[1];
				snake_length++;
				#ifdef DEBUG_MODE
					std::cout << "If if \t";
				#endif
				
			}
			else if (snake_length >= SNAKE_MAX_LEN){

				map[snake_old_head_var[0]][snake_old_head_var[1]].snake_head = 0;
				map[snake_head_var[0]][snake_head_var[1]].snake_head = 1;	
				map[snake_old_head_var[0]][snake_old_head_var[1]].snake_body = 1;
				map[snake_location[0][SNAKE_MAX_LEN-1]][snake_location[1][SNAKE_MAX_LEN-1]].snake_body = 0;
				array_shift(snake_location, SNAKE_MAX_LEN, 1);
				snake_location[0][0] = snake_old_head_var[0];
				snake_location[1][0] = snake_old_head_var[1];
				#ifdef DEBUG_MODE
					std::cout << "If else if \t";
				#endif
			}
			
			else {
				
				map[snake_old_head_var[0]][snake_old_head_var[1]].snake_head = 0;
				map[snake_head_var[0]][snake_head_var[1]].snake_head = 1;	
				map[snake_old_head_var[0]][snake_old_head_var[1]].snake_body = 1;
				snake_location[0][0] = snake_old_head_var[0];
				snake_location[1][0] = snake_old_head_var[1];
				snake_length++;
				#ifdef DEBUG_MODE
					std::cout << "If else \t";
				#endif

			}	
		}
		
		//if there's no life in cell
		else {
			
			if (snake_length > 0 && snake_length < SNAKE_MAX_LEN){
				
				map[snake_old_head_var[0]][snake_old_head_var[1]].snake_head = 0;
				map[snake_head_var[0]][snake_head_var[1]].snake_head = 1;	
				map[snake_old_head_var[0]][snake_old_head_var[1]].snake_body = 1;
				map[snake_location[0][snake_length-1]][snake_location[1][snake_length-1]].snake_body = 0;
				array_shift(snake_location, SNAKE_MAX_LEN, 1);
				snake_location[0][0] = snake_old_head_var[0];
				snake_location[1][0] = snake_old_head_var[1];
				#ifdef DEBUG_MODE
					std::cout << "Else if \t";
				#endif
			}
			else if (snake_length >= SNAKE_MAX_LEN){
				
				map[snake_old_head_var[0]][snake_old_head_var[1]].snake_head = 0;
				map[snake_head_var[0]][snake_head_var[1]].snake_head = 1;	
				map[snake_old_head_var[0]][snake_old_head_var[1]].snake_body = 1;
				map[snake_location[0][SNAKE_MAX_LEN-1]][snake_location[1][SNAKE_MAX_LEN-1]].snake_body = 0;
				array_shift(snake_location, SNAKE_MAX_LEN, 1);
				snake_location[0][0] = snake_old_head_var[0];
				snake_location[1][0] = snake_old_head_var[1];
				#ifdef DEBUG_MODE
					std::cout << "Else else if \t";
				#endif
			}
			
			else{
				
				map[snake_old_head_var[0]][snake_old_head_var[1]].snake_head = 0;
				map[snake_head_var[0]][snake_head_var[1]].snake_head = 1;	
				
				#ifdef DEBUG_MODE
					std::cout << "Else else \t";
				#endif
			}
		}
		#ifdef DEBUG_MODE
			std::cout << "Snake length " << snake_length << "\t";
		#endif
		
		if (snake_length >= SNAKE_MAX_LEN){
			snake_alive = 0;
			hatching_time = 0;
			destroy_snake (map);
			lay_egg(map, snake_head_var[0], snake_head_var[1]);
		
		}
	}
	
	

	
	else {
		hatching_time++;
		hatch_egg (map);
	}
}

//object destructor
Snake::~Snake(){
	
}