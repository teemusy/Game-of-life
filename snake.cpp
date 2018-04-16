#include <curses.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>

#include "constants.h"
#include "snake.h"



void Snake::set_head_location (int loc_x, int loc_y){
	
	snake_location[0][0] = loc_y;
	snake_location[0][1] = loc_x;
	snake_length = 0;
}

void Snake::move_snake (struct cell_info map[ROWS][COLUMNS]){
	int direction, legal_direction, old_location[2];
	
	map[snake_location[0][0]][snake_location[0][1]].snake_head = 0;
	
	old_location[0] = snake_location[0][0];
	old_location[1] = snake_location[0][1];
	
	//check for legal direction
	do{
		direction = random_direction ();
		legal_direction = 1;
		if((snake_location[0][1] == COLUMNS-1 && direction == 6) ||
			(snake_location[0][1] == 0 && direction == 4) ||
			(snake_location[0][0] == ROWS-1 && direction == 2) ||
			(snake_location[0][0] == 0 && direction == 8)){
				
				legal_direction = 0;
		}
	}
	while(!legal_direction);
	
	switch (direction){
		case 2:
			snake_location[0][0]++;
			mvprintw(40, 40, "2");
			break;		
		
		case 4:
			snake_location[0][1]--;
			mvprintw(40, 40, "4");
			break;		
		
		case 6:
			snake_location[0][1]++;
			mvprintw(40, 40, "6");
			break;		
		
		case 8:
			snake_location[0][0]--;
			mvprintw(40, 40, "8");
			break;
		default:
			break;
		
	}
	
	map[snake_location[0][0]][snake_location[0][1]].snake_head = 1;
	
	//increase snake length
	if (map[snake_location[0][0]][snake_location[0][1]].current_status == 1){
		snake_length++;
		map[snake_location[0][0]][snake_location[0][1]].current_status = 0;
	}
}

Snake::~Snake(){
	
}