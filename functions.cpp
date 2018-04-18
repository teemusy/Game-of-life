#include <curses.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include "constants.h"

/*********************************************************************
*    FUNCTIONS                                                     *
**********************************************************************/
/*********************************************************************
;	F U N C T I O N    D E S C R I P T I O N
;---------------------------------------------------------------------
; NAME: random_direction
; DESCRIPTION: Gives 4 different random directions
;	Input: None	
;	Output: Direction as integer
;  Used global variables:
; REMARKS when using this function:
;*********************************************************************/
int random_direction (){
	int random_value;
	
	random_value = (rand() % 100) + 1;
	
	if (random_value < 25){
		random_value = 2;
	}	
	
	else if (random_value >= 25 && random_value < 50){
		random_value = 4;
	}	
	
	else if (random_value >= 50 && random_value < 75){
		random_value = 6;
	}
	else {
		random_value = 8;
	}
	
	return random_value;
}
/*********************************************************************
;	F U N C T I O N    D E S C R I P T I O N
;---------------------------------------------------------------------
; NAME: random_value_filler
; DESCRIPTION: Returns either 1 or 0
;	Input: None
;	Output: Randomly 1 or 0
;  Used global variables:
; REMARKS when using this function:
;*********************************************************************/
int random_value_filler (){
	int random_value;
	
	random_value = (rand() % 100);
	
	if (random_value < FILL_PERCENTAGE){
		random_value = 1;
	}
	else {
		random_value = 0;
	}
	
	return random_value;
}
/*********************************************************************
;	F U N C T I O N    D E S C R I P T I O N
;---------------------------------------------------------------------
; NAME: map_filler
; DESCRIPTION: Fills map struct current status with random bits
;	Input: Struct
;	Output: None
;  Used global variables:
; REMARKS when using this function:
;*********************************************************************/
void map_filler (struct cell_info map[ROWS][COLUMNS]){
	int i, j;
	for(i = 0; i < ROWS; i++){
		for(j = 0; j < COLUMNS; j++){
			#ifdef DEBUG_MODE
				std::cout << "i: " << i << "j: " << j << "\t";
			#endif
			map[i][j].current_status = random_value_filler ();
			map[i][j].future_status = 0;
			map[i][j].snake_head = 0;
			map[i][j].snake_body = 0;
			map[i][j].egg = 0;

		}
	}
	#ifdef DEBUG_MODE
		//to clear buffer
		std::cout << "\n\n\n";
	#endif
}
/*********************************************************************
;	F U N C T I O N    D E S C R I P T I O N
;---------------------------------------------------------------------
; NAME: draw_creatures
; DESCRIPTION: Draws creatures using array cells as locations, uses ncurses
;	Input: Struct, ncurses window
;	Output: None
;  Used global variables:
; REMARKS when using this function:
;*********************************************************************/
void draw_creatures (struct cell_info map[ROWS][COLUMNS], WINDOW *local_win){
	int i, j;
	
	//declare color pairs
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLUE);
	init_pair(3, COLOR_RED, COLOR_GREEN);
	init_pair(4, COLOR_BLACK, COLOR_YELLOW);
	init_pair(5, COLOR_YELLOW, COLOR_BLUE);
		
	//draw creatures
	for(i = 0; i < ROWS; i++){
		
		for(j = 0; j < COLUMNS; j++){
			if (map[i][j].current_status){
				wattron(local_win, COLOR_PAIR(2));
				mvwprintw(local_win, i+1, j+1, "@");
				wattroff(local_win, COLOR_PAIR(2));	
			}
			else if (map[i][j].snake_head){
				
				wattron(local_win, COLOR_PAIR(4));
				mvwprintw(local_win, i+1, j+1, "X");
				wattroff(local_win, COLOR_PAIR(4));	

			}			
			
			else if (map[i][j].snake_body){
				
				wattron(local_win, COLOR_PAIR(4));
				mvwprintw(local_win, i+1, j+1, "o");
				wattroff(local_win, COLOR_PAIR(4));	

			}
	
			
			else if (map[i][j].egg){
				wattron(local_win, COLOR_PAIR(1));
				mvwprintw(local_win, i+1, j+1, "O");
				wattroff(local_win, COLOR_PAIR(1));	
			}
			else/* if (map[i][j].current_status == 0)*/{
				wattron(local_win, COLOR_PAIR(2));
				mvwprintw(local_win, i+1, j+1, " ");
				wattroff(local_win, COLOR_PAIR(2));	
			}		
		}
	}
}
/*********************************************************************
;	F U N C T I O N    D E S C R I P T I O N
;---------------------------------------------------------------------
; NAME: draw_static
; DESCRIPTION: Draws borders for creatures, uses ncurses
;	Input: Ncurses window
;	Output: None
;  Used global variables:
; REMARKS when using this function:
;*********************************************************************/
void draw_static (WINDOW *local_win){
	int i;
	
	//declare color pairs
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLUE);
	init_pair(3, COLOR_RED, COLOR_GREEN);
	
	//draw horizontal borders
	wattron(local_win, COLOR_PAIR(1));
	for(i = 0; i < COLUMNS + 2; i++){
		mvwprintw(local_win, 0, i, "#");
		mvwprintw(local_win, ROWS + 1, i, "#");
	}
	//draw vertical borders
	for(i = 0; i < ROWS + 2; i++){
		mvwprintw(local_win, i, 0, "#");
		mvwprintw(local_win, i, COLUMNS + 1, "#");
	}
	wattroff(local_win, COLOR_PAIR(1));
}
/*********************************************************************
;	F U N C T I O N    D E S C R I P T I O N
;---------------------------------------------------------------------
; NAME: sleep_for_seconds
; DESCRIPTION: Sleeps for wanted amount of time
;	Input: Seconds as float number
;	Output: None
;  Used global variables:
; REMARKS when using this function:
;*********************************************************************/
void sleep_for_seconds (float s){ 
	int sec = s*1000000; 
	
	usleep(sec); 
} 
/*********************************************************************
;	F U N C T I O N    D E S C R I P T I O N
;---------------------------------------------------------------------
; NAME: copy_map
; DESCRIPTION: Copies the second layer of the array to the first one, second layer acts as a temp
;	Input: Struct
;	Output: None
;  Used global variables:
; REMARKS when using this function:
;*********************************************************************/
void copy_map (struct cell_info map[ROWS][COLUMNS]){
	int i, j, temp_value;
	
	for (i = 0; i < ROWS; i++){
		for (j = 0; j < COLUMNS; j++){
			temp_value = map [i][j].future_status;
			map [i][j].current_status = temp_value;
		}
	}
}
/*********************************************************************
;	F U N C T I O N    D E S C R I P T I O N
;---------------------------------------------------------------------
; NAME: print_count
; DESCRIPTION: Updates count on screen, should combine with print_stats function
;	Input: Integer
;	Output: None
;  Used global variables: DEBUG_MODE
; REMARKS when using this function:
;*********************************************************************/
void print_count (int creature_count){
	
	#ifdef DEBUG_MODE
	
		printf("Creature count: %d \n", creature_count);
	#else
		init_pair(1, COLOR_RED, COLOR_BLACK);
		init_pair(2, COLOR_RED, COLOR_BLUE);
		init_pair(3, COLOR_RED, COLOR_GREEN);
		
		attron(COLOR_PAIR(1));
		mvprintw(ROWS + 4, 1, "Creature count: %d \n", creature_count);
		attroff(COLOR_PAIR(1));	
	#endif
}
/*********************************************************************
;	F U N C T I O N    D E S C R I P T I O N
;---------------------------------------------------------------------
; NAME: update_life
; DESCRIPTION: Determines if cells live, die or born again
;	Input: Struct
;	Output: None
;  Used global variables:
; REMARKS when using this function:
;*********************************************************************/
void update_life (struct cell_info map[ROWS][COLUMNS]) {

	int i, j, life_count, dead_count, creature_count;
	creature_count = 0;
	for (i = 0; i < ROWS; i++){
		for (j = 0; j < COLUMNS; j++){
			
			//keeps track on creature count
			if (map [i][j].current_status){
				creature_count++;
			}

			//check if it's legal array value, eg. not -1
			//check if cell has life and if it's inside the array
			//if cell has no life it checks if there's life around it
			if (!map [i][j].snake_head && !map [i][j].snake_body && !map[i][j].egg){
				//check north
				if (map [i][j].current_status == 1 && i > 0){
					if (NORTH && !SNAKE_NORTH && !SNAKE_BODY_NORTH && !EGG_NORTH){
						life_count++;
					}
				}
				else if (!map [i][j].current_status && i > 0){
					if (NORTH && !SNAKE_NORTH && !SNAKE_BODY_NORTH && !EGG_NORTH){
						dead_count++;
					}
				}
				//south
				if (map [i][j].current_status && i < ROWS-1){
					if (SOUTH && !SNAKE_SOUTH && !SNAKE_BODY_SOUTH && !EGG_SOUTH){
						life_count++;
					}	
				}
				else if (!map [i][j].current_status && i < ROWS-1){
					if (SOUTH && !SNAKE_SOUTH && !SNAKE_BODY_SOUTH && !EGG_SOUTH){
						dead_count++;
					}	
				}
				//east
				if (map [i][j].current_status && j < COLUMNS-1){
					if (EAST && !SNAKE_EAST && !SNAKE_BODY_EAST && !EGG_EAST){
						life_count++;
					}
				}
				else if (!map [i][j].current_status && j < COLUMNS-1){
					if (EAST && !SNAKE_EAST && !SNAKE_BODY_EAST && !EGG_EAST){
						dead_count++;
					}
				}
				//west
				if (map [i][j].current_status && j > 0){
					if (WEST && !SNAKE_WEST && !SNAKE_BODY_WEST && !EGG_WEST){
						life_count++;
					}
				}	
				else if (!map [i][j].current_status && j > 0){
					if (WEST && !SNAKE_WEST && !SNAKE_BODY_WEST && !EGG_WEST){
						dead_count++;
					}
				}				
				//northeast
				if (map [i][j].current_status && i > 0 && j < COLUMNS-1){
					if (NORTHEAST && !SNAKE_NORTHEAST && !SNAKE_BODY_NORTHEAST && !EGG_NORTHEAST){
						life_count++;
					}
				}
				else if (!map [i][j].current_status && i > 0 && j < COLUMNS-1){
					if (NORTHEAST && !SNAKE_NORTHEAST && !SNAKE_BODY_NORTHEAST && !EGG_NORTHEAST){
						dead_count++;
					}
				}
				

				//southeast
				if (map [i][j].current_status && i < ROWS-1 && j < COLUMNS-1){
					if (SOUTHEAST && !SNAKE_SOUTHEAST && !SNAKE_BODY_SOUTHEAST && !EGG_SOUTHEAST){
						life_count++;
					}	
				}
				else if (!map [i][j].current_status && i < ROWS-1 && j < COLUMNS-1){
					if (SOUTHEAST && !SNAKE_SOUTHEAST && !SNAKE_BODY_SOUTHEAST && !EGG_SOUTHEAST){
						dead_count++;
					}	
				}
				
				//northwest
				if (map [i][j].current_status && i > 0 && j > 0){
					if (NORTHWEST && !SNAKE_NORTHWEST && !SNAKE_BODY_NORTHWEST && !EGG_NORTHWEST){
						life_count++;
					}
				}
				else if (!map [i][j].current_status && i > 0 && j > 0){
					if (NORTHWEST && !SNAKE_NORTHWEST && !SNAKE_BODY_NORTHWEST && !EGG_NORTHWEST){
						dead_count++;
					}
				}
				//southwest
				if (map [i][j].current_status && i < ROWS-1 && j > 0){
					if (SOUTHWEST && !SNAKE_SOUTHWEST && !SNAKE_BODY_SOUTHWEST && !EGG_SOUTHWEST){
						life_count++;
					}
				}
				else if (!map [i][j].current_status && i < ROWS-1 && j > 0){
					if (SOUTHWEST && !SNAKE_SOUTHWEST && !SNAKE_BODY_SOUTHWEST && !EGG_SOUTHWEST){
						dead_count++;
					}
				}
				
				//determine if cell lives, dies or a new one borns, update to second layer of map
				if (life_count < UNDERPOPULATION_LIMIT){
					map[i][j].future_status = 0;
				}
				else if (life_count >= LIVE_MIN && life_count <= LIVE_MAX && !map[i][j].snake_body && !map[i][j].snake_head && !map[i][j].egg){
					map[i][j].future_status = 1;
				}
				else if (life_count > OVERPOPULATION_LIMIT){
					map[i][j].future_status = 0;	
				}
				
				if (dead_count == REBIRTH_LIMIT && !map[i][j].snake_body && !map[i][j].snake_head && !map[i][j].egg){
					map[i][j].future_status = 1;
				}
			}
			//reset counters for next cell
			life_count = 0;
			dead_count = 0;
		}
	}
	print_count (creature_count);
	//copies second, temporary layer of the map to the first one to be printed
	copy_map(map);
}

/*********************************************************************
;	F U N C T I O N    D E S C R I P T I O N
;---------------------------------------------------------------------
; NAME: debug_print
; DESCRIPTION: Allows easier debugging by disabling ncurses and printing map to console
;	Input: Struct
;	Output: None
;  Used global variables:
; REMARKS when using this function:
;*********************************************************************/
void debug_print (struct cell_info map[ROWS][COLUMNS]){
	int i, j;
	
	for (i = 0; i < ROWS; i++){
		for (j = 0; j < COLUMNS; j++){
			if (map[i][j].current_status){
				std::cout << "@";
			}
			else if (map[i][j].snake_head){
				
				std::cout << "X";
			}			
			
			else if (map[i][j].snake_body){
				
				std::cout << "o";

			}
			else if (!map[i][j].current_status){
				
				std::cout << ".";
			}
		}
		printf("\n");
	}
	printf("\n");
}
/*********************************************************************
;	F U N C T I O N    D E S C R I P T I O N
;---------------------------------------------------------------------
; NAME: print_stats
; DESCRIPTION: Updates statistics on screen
;	Input: Integer
;	Output: None
;  Used global variables: DEBUG_MODE
; REMARKS when using this function:
;*********************************************************************/
void print_stats (int iteration){
	
	#ifdef DEBUG_MODE
		printf("Current iteration: %d \n", iteration);
	#else
		init_pair(1, COLOR_RED, COLOR_BLACK);
		init_pair(2, COLOR_RED, COLOR_BLUE);
		init_pair(3, COLOR_RED, COLOR_GREEN);
		
		attron(COLOR_PAIR(1));
		mvprintw(ROWS + 3, 1, "Current iteration: %d", iteration);
		attroff(COLOR_PAIR(1));	
	#endif
}

/*********************************************************************
;	F U N C T I O N    D E S C R I P T I O N
;---------------------------------------------------------------------
; NAME: map_reader
; DESCRIPTION: Reads map from file
;	Input: Struct to store map info
;	Output: None
;  Used global variables:
; REMARKS when using this function:
;*********************************************************************/
void map_reader(struct cell_info map[ROWS][COLUMNS]){
	
	FILE *myFile;
    myFile = fopen("map.txt", "r");
	//read file into array
    int numberArray[ROWS][COLUMNS];
    int i, j, temp_value;

    for (i = 0; i < ROWS; i++)
    {	for(j = 0; j < COLUMNS; j++){
			fscanf(myFile, "%d", &numberArray[i][j]);
		}
    }

    for (i = 0; i < ROWS; i++){
		for(j = 0; j < COLUMNS; j++){
			temp_value = numberArray[i][j];
			map[i][j].current_status = temp_value;
			map[i][j].snake_head = 0;
			map[i][j].snake_body = 0;
			map[i][j].future_status = 0;
			map[i][j].egg = 0;

		}
	} 
	fclose(myFile);
}
/*********************************************************************
;	F U N C T I O N    D E S C R I P T I O N
;---------------------------------------------------------------------
; NAME: menu_function
; DESCRIPTION: Main menu for the simulation
;	Input: Float speed as pointer
;	Output: Menu choice as integer
;  Used global variables: None
; REMARKS when using this function:
;*********************************************************************/
int menu_function(WINDOW *local_win, float *speed){
	int choice, menu_choice, highlight;
	
	//menu choices
	const char *a[2];
	a[0] = "Randomize map";
	a[1] = "Load from file map.txt";
	//a[2] = "Pause";
	
	//add length check
	int choice_len = 2;
	
	keypad(local_win, true);
	
	mvwprintw(local_win, ROWS-2, COLUMNS/4, "Rebirth speed is %.3f seconds.", *speed);
	mvwprintw(local_win, ROWS-1, COLUMNS/4, "Press left or right to increase or decrease speed.");
	
	mvwprintw(local_win, 1, COLUMNS/4, "   _____          __  __ ______    ____  ______   _      _____ ______ ______ ");
	mvwprintw(local_win, 2, COLUMNS/4, "  / ____|   /\\   |  \\/  |  ____|  / __ \\|  ____| | |    |_   _|  ____|  ____|");
	mvwprintw(local_win, 3, COLUMNS/4, " | |  __   /  \\  | \\  / | |__    | |  | | |__    | |      | | | |__  | |__   ");
	mvwprintw(local_win, 4, COLUMNS/4, " | | |_ | / /\\ \\ | |\\/| |  __|   | |  | |  __|   | |      | | |  __| |  __|  ");
	mvwprintw(local_win, 5, COLUMNS/4, " | |__| |/ ____ \\| |  | | |____  | |__| | |      | |____ _| |_| |    | |____ ");
	mvwprintw(local_win, 6, COLUMNS/4, "  \\_____/_/    \\_\\_|  |_|______|  \\____/|_|      |______|_____|_|    |______|");

	highlight = 0;
	while (1){
		int i;
		//add length of choices to for loop
		for (i = 0; i < choice_len; i++){
			if (i == highlight){
				wattron(local_win, A_REVERSE);
				mvwprintw(local_win, i+20, COLUMNS/4, "%s", a[i]);
				wattroff(local_win, A_REVERSE);
				menu_choice = i;
			}
			else {
				mvwprintw(local_win, i+20, COLUMNS/4, "%s", a[i]);
			}
		}
		
	
		choice = wgetch(local_win);
		
		switch(choice){
			case KEY_UP:
				highlight--;
				if (highlight <= 0){
					highlight = 0;
				}
				break;
				
			case KEY_DOWN:
				highlight++;
				if (highlight > choice_len){
					highlight = 2;
				}
				break;
			case KEY_RIGHT:
				*speed = *speed + 0.005;
				if (*speed > 10){
					*speed = 10;
				}
				mvwprintw(local_win, ROWS-2, COLUMNS/4, "Rebirth speed is %.3f seconds.", *speed);
				break;			
				
			case KEY_LEFT:
				*speed = *speed - 0.005;
				if (*speed <= 0){
					*speed = 0.01;
				}
				mvwprintw(local_win, ROWS-2, COLUMNS/4, "Rebirth speed is %.3f seconds.", *speed);
				break;
				
			default:
				break;
		}
		
		if(choice == 10){
			break;	
		}
	}
	
	return menu_choice;
}
/*********************************************************************
;	F U N C T I O N    D E S C R I P T I O N
;---------------------------------------------------------------------
; NAME: options
; DESCRIPTION: Option menu that show during the simulation
;	Input: Ncurses window, gamespeed pointer
;	Output: Menu choice
;  Used global variables:
; REMARKS when using this function: Not in use as it pauses the simulation
;*********************************************************************/
int options(WINDOW *local_win, float *speed){
	int choice, menu_choice, highlight;
	
	//menu choices
	const char *a[5];
	a[0] = "Randomize map";
	a[1] = "Load from file map.txt";
	a[2] = "Add snake";
	a[3] = "Remove snake";
	a[4] = "Pause/resume";
	
	
	//add length check
	int choice_len = 5;
	
	keypad(local_win, true);
	
	
	nodelay(local_win, true);

	highlight = 0;
	while (1){
		int i;
		//add length of choices to for loop
		for (i = 0; i < choice_len; i++){
			if (i == highlight){
				wattron(local_win, A_REVERSE);
				mvwprintw(local_win, i+1, 1, "%s", a[i]);
				wattroff(local_win, A_REVERSE);
				menu_choice = i;
			}
			else {
				mvwprintw(local_win, i+1, 1, "%s", a[i]);
			}
		}
		
		choice = wgetch(local_win);
		
		switch(choice){
			case KEY_UP:
				highlight--;
				if (highlight <= 0){
					highlight = 0;
				}
				break;
				
			case KEY_DOWN:
				highlight++;
				if (highlight > choice_len){
					highlight = 2;
				}
				break;
			case KEY_RIGHT:
				*speed = *speed + 0.005;
				if (*speed > 10){
					*speed = 10;
				}
				mvwprintw(local_win, ROWS-2, COLUMNS/4, "Rebirth speed is %.3f seconds.", *speed);
				break;			
				
			case KEY_LEFT:
				*speed = *speed - 0.005;
				if (*speed <= 0){
					*speed = 0.01;
				}
				mvwprintw(local_win, ROWS-2, COLUMNS/4, "Rebirth speed is %.3f seconds.", *speed);
				break;
				
			default:
				break;
		}
		
		if(choice == 10){
			break;	
		}
	}
	
	return menu_choice;
}
/*********************************************************************
;	F U N C T I O N    D E S C R I P T I O N
;---------------------------------------------------------------------
; NAME: array_shift
; DESCRIPTION: Shifts [2][x] array x-cells left or right
;	Input: 2D array, size of x, direction 1/-1
;	Output: None
;  Used global variables:
; REMARKS when using this function:
;*********************************************************************/
void array_shift(int arr[2][SNAKE_MAX_LEN], int len, int dir){
	int i, temp_array[2][100], temp0, temp1, last0, last1;

	switch(dir){
		case 1:
			last0 = arr[0][len-1];
			last1 = arr[1][len-1];
			for (i=0; i < len; i++){
				temp0 = arr[0][i];
				temp1 = arr[1][i];
				temp_array[0][i] = temp0;
				temp_array[1][i] = temp1;
			}
			
			for(i = 0; i < len; i++){
				if(i < len - 1){
					temp0 = temp_array[0][i];
					temp1 = temp_array[1][i];
					arr[0][i+1] = temp0;
					arr[1][i+1] = temp1;
				}
			}
			arr[0][0] = last0;
			arr[1][0] = last1;
			break;
		case -1:
			last0 = arr[0][0];
			last1 = arr[1][0];
			for (i=0; i < len; i++){
				temp0 = arr[0][i];
				temp1 = arr[1][i];
				temp_array[0][i] = temp0;
				temp_array[1][i] = temp1;
			}
			for(i = len; i > 0; i--){
				if(i > 0){
					temp0 = temp_array[0][i];
					temp1 = temp_array[1][i];
					arr[0][i-1] = temp0;
					arr[1][i-1] = temp1;
				}
			}
			arr[0][len-1] = last0;
			arr[1][len-1] = last1;
			break;
	}
}
/*********************************************************************
;	F U N C T I O N    D E S C R I P T I O N
;---------------------------------------------------------------------
; NAME:
; DESCRIPTION:
;	Input:
;	Output:
;  Used global variables:
; REMARKS when using this function:
;*********************************************************************/