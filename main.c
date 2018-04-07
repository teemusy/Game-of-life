/*compile with -lncurses option*/

/*-------------------------------------------------------------------*
*    HEADER FILES                                                    *
*--------------------------------------------------------------------*/
#include <stdio.h>
#include <curses.h>
#include <string.h>
#include <menu.h>
#include <stdlib.h>

/*-------------------------------------------------------------------*
*    GLOBAL VARIABLES                                                *
*--------------------------------------------------------------------*/
/* Control flags */

/* Global constants */
//determines the size of the map
#define ROWS 50
#define COLUMNS 100
#define LAYERS 2
#define TIME_BETWEEN_REBIRTH 0.2
//to determine initial seed
#define FILL_PERCENTAGE 30
//define directions
#define NORTH map [i-1][j].current_status
#define SOUTH map [i+1][j].current_status
#define EAST map [i][j+1].current_status
#define WEST map [i][j-1].current_status
#define NORTHEAST map [i-1][j+1].current_status
#define SOUTHEAST map [i+1][j+1].current_status
#define NORTHWEST map [i-1][j-1].current_status
#define SOUTHWEST map [i+1][j-1].current_status
//define game rules
#define UNDERPOPULATION_LIMIT 2
#define LIVE_MIN 2
#define LIVE_MAX 3
#define OVERPOPULATION_LIMIT 3
#define REBIRTH_LIMIT 3

/* Global variables */

//debug mode disables ncurses for easier debugging, recommended to decrease map size
int DEBUG_MODE;
/* Global structures */
struct cell_info {
	   int current_status;
	   int future_status;
	   int snake_head;
	   int snake_direction;
};

/*-------------------------------------------------------------------*
*    FUNCTION PROTOTYPES                                             *
*--------------------------------------------------------------------*/

//fills both layers of map with 1 or 0
int random_value_filler ();
//fill map with random number
void new_map_filler (struct cell_info map[ROWS][COLUMNS]);
//draw static stuff
void draw_static (WINDOW *local_win);
//draw creatures with ncurses
void new_draw_creatures (struct cell_info map[ROWS][COLUMNS], WINDOW *local_win);
//sleep function
void sleep_for_seconds (float s);
//check if creature lives, dies or regenerates, then update map
void new_update_life (struct cell_info map[ROWS][COLUMNS]);
//print function for debugging
void debug_print (struct cell_info map[ROWS][COLUMNS]);
//copy array layer
void new_copy_map (struct cell_info map[ROWS][COLUMNS]);
//print statistics
void print_stats (int iteration);
void print_count (int creature_count);
void map_reader(struct cell_info map[ROWS][COLUMNS]);

int menu_function(WINDOW *local_win, float *speed);



void snake_mover (int *snake_x, int *snake_y, struct cell_info map[ROWS][COLUMNS]);
int random_direction ();




/*********************************************************************
*    MAIN PROGRAM                                                      *
**********************************************************************/

//TODO
//-pause function
//-move cmd line input to function
//-magic numbers
//-move to using struct
//for better menu
//-streamline update_life function

void main(int argc, char *argv[]) {
	
	int random_value, iteration, size_x, size_y, i, menu_choice;
	char cmd_line_input[50];
	//to make it possible to pause game
	float game_speed;
	
	struct cell_info new_map[ROWS][COLUMNS];
	
	
	
	//snake test init
	int snake_x = 25, snake_y = 25;
	
	
	
	
	
	srand( time(NULL) ); //Randomize seed initialization for map_fill
	iteration = 0;
	game_speed = TIME_BETWEEN_REBIRTH;
	
	//cmd line input
	for (i = 0; i < argc; i++){
		//checks for flags
		if (argc > 1){
			sscanf(argv[1], "%s", &cmd_line_input[50]);
			strcpy (cmd_line_input, argv[1]);
				if (strcmp(cmd_line_input, "-d") == 0){
					DEBUG_MODE = 1;
				}
		}
	}
	
	//check if debug mode is on, else init ncurses
	if (DEBUG_MODE == 1){
		new_map_filler(new_map);
		while(true){
			debug_print (new_map);
			//print iteration
			print_stats(iteration);
			iteration++;
			sleep_for_seconds(game_speed);
			//update_life (map);
		}
	}
	else {
		initscr(); //ncurses init
		
		/*get screen size for terminal, not in use 
		because it makes it harder to init map size*/
		getmaxyx(stdscr, size_x, size_y);
		printf("x: %d, y: %d\n", size_x, size_y);
		
		curs_set(0);
		start_color();
		//init windows, size y, size x, location y, location x
		WINDOW* map_window = newwin(ROWS + 2, COLUMNS + 2, 0, 0);
		WINDOW* text_window = newwin(5, COLUMNS + 2, ROWS+2, 0);
		WINDOW* menu_window = newwin(ROWS + 2, 20, 0, COLUMNS+2);
		//draws borders
		
		box(text_window,0,0);
		box(menu_window,0,0);
		
		//run menu
		menu_choice = menu_function(map_window, &game_speed);
		draw_static (map_window); 
		switch(menu_choice){
			case 0:
				new_map_filler(new_map);
				break;
			case 1:
				map_reader (new_map);
				break;
			default:
				new_map_filler (new_map);
				break;
		}
		
		
		
		//MAIN LOOP
		while(true){
			//draw_creatures (map, map_window);
			new_draw_creatures (new_map, map_window);
			//print iteration
			print_stats(iteration);
			
			refresh();
			wrefresh(map_window);
			wrefresh(text_window);
			wrefresh(menu_window);
			iteration++;
			sleep_for_seconds(game_speed);
			//update_life (map);
			new_update_life (new_map);
			
			
			
			
			
			snake_mover (&snake_x, &snake_y, new_map);
			mvprintw(ROWS + 5, 1, "Snake_x, snake_y: %d %d", snake_x, snake_y);
			
			
			
		}
		endwin(); /*End curses mode */
	}
	
}/* end of main */

/*********************************************************************
*    FUNCTIONS                                                     *
**********************************************************************/
void snake_mover (int *snake_x, int *snake_y, struct cell_info map[ROWS][COLUMNS]){
	int direction, i, j, legal_direction, temp_value;
	
	
	map[*snake_y][*snake_x].snake_head = 0;
	map[*snake_y][*snake_x].snake_direction = 0;
	map[*snake_y][*snake_x].current_status = 0;
	map[*snake_y][*snake_x].future_status = 0;
	
	//check for legal direction
	do{
		direction = random_direction ();
		legal_direction = 1;
		if((*snake_x == COLUMNS-1 && direction == 6) ||
			(*snake_x == 0 && direction == 4) ||
			(*snake_y == ROWS-1 && direction == 2) ||
			(*snake_y == 0 && direction == 8)){
				
				legal_direction = 0;
		}
	}
	while(!legal_direction);
	
	
	switch (direction){
		case 2:
			*snake_y+=1;
			mvprintw(ROWS + 5, 30, "south");
			map[*snake_y][*snake_x].snake_direction = 2;
			break;		
		
		case 4:
			*snake_x-=1;
			mvprintw(ROWS + 5, 30, "west");
			map[*snake_y][*snake_x].snake_direction = 4;
			break;		
		
		case 6:
			*snake_x+=1;
			mvprintw(ROWS + 5, 30, "east");
			map[*snake_y][*snake_x].snake_direction = 6;
			break;		
		
		case 8:
			*snake_y-=1;
			mvprintw(ROWS + 5, 30, "north");
			map[*snake_y][*snake_x].snake_direction = 8;
			break;
		default:
			break;
		
	}
	
	map[*snake_y][*snake_x].snake_head = 1;
	
}
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
; DESCRIPTION: Fills map array struct current status with random bits
;	Input: Array, struct
;	Output: None
;  Used global variables:
; REMARKS when using this function:
;*********************************************************************/
void new_map_filler (struct cell_info map[ROWS][COLUMNS]){
	int i, j;
	
	for(i = 0; i < ROWS; i++){
		for(j = 0; j < COLUMNS; j++){
			
			map[i][j].current_status = random_value_filler ();
			map[i][j].snake_head = 0;
			map[i][j].snake_direction = 0;
		}
	}
}




/*********************************************************************
;	F U N C T I O N    D E S C R I P T I O N
;---------------------------------------------------------------------
; NAME: draw_creatures
; DESCRIPTION: Draws creatures using array cells as locations, uses ncurses
;	Input: Array
;	Output: None
;  Used global variables:
; REMARKS when using this function:
;*********************************************************************/
void new_draw_creatures (struct cell_info map[ROWS][COLUMNS], WINDOW *local_win){
	int i, j;
	
	//declare color pairs
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLUE);
	init_pair(3, COLOR_RED, COLOR_GREEN);
	init_pair(4, COLOR_BLACK, COLOR_YELLOW);
		
	//draw creatures
	for(i = 0; i < ROWS; i++){
		
		for(j = 0; j < COLUMNS; j++){
			if (map[i][j].current_status == 1){
				wattron(local_win, COLOR_PAIR(2));
				mvwprintw(local_win, i+1, j+1, "@");
				wattroff(local_win, COLOR_PAIR(2));	
			}
			else if (map[i][j].snake_head == 1){
				
				switch(map[i][j].snake_direction){
					case 2:
						wattron(local_win, COLOR_PAIR(4));
						mvwprintw(local_win, i+1, j+1, "u");
						wattroff(local_win, COLOR_PAIR(4));	
						break;					
					case 4:
						wattron(local_win, COLOR_PAIR(4));
						mvwprintw(local_win, i+1, j+1, "<");
						wattroff(local_win, COLOR_PAIR(4));	
						break;					
					case 6:
						wattron(local_win, COLOR_PAIR(4));
						mvwprintw(local_win, i+1, j+1, ">");
						wattroff(local_win, COLOR_PAIR(4));	
						break;					
					case 8:
						wattron(local_win, COLOR_PAIR(4));
						mvwprintw(local_win, i+1, j+1, "^");
						wattroff(local_win, COLOR_PAIR(4));	
						break;
					
					
				}

			}
			else if (map[i][j].current_status == 0){
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
;	Input: None
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
; NAME: update_life
; DESCRIPTION: Determines if cells live, die or born again
;	Input: Array
;	Output: None
;  Used global variables:
; REMARKS when using this function:
;*********************************************************************/
void new_update_life (struct cell_info map[ROWS][COLUMNS]) {

	int i, j, life_count, dead_count, creature_count;
	creature_count = 0;
	for (i = 0; i < ROWS; i++){
		for (j = 0; j < COLUMNS; j++){
			
			//keeps track on creature count
			if (map [i][j].current_status == 1){
				creature_count++;
			}

			//check if it's legal array value, eg. not -1
			//check if cell has life and if it's inside the array
			//if cell has no life it checks if there's life around it
			
			
			
			//check north
			if (map [i][j].current_status == 1 && i > 0){
				if (NORTH == 1){
					life_count++;
				}
			}
			else if (map [i][j].current_status == 0 && i > 0){
				if (NORTH == 1){
					dead_count++;
				}
			}
			//south
			if (map [i][j].current_status == 1 && i < ROWS){
				if (SOUTH == 1){
					life_count++;
				}	
			}
			else if (map [i][j].current_status == 0 && i < ROWS){
				if (SOUTH == 1){
					dead_count++;
				}	
			}
			//east
			if (map [i][j].current_status == 1 && j < COLUMNS){
				if (EAST == 1){
					life_count++;
				}
			}
			else if (map [i][j].current_status == 0 && j < COLUMNS){
				if (EAST == 1){
					dead_count++;
				}
			}
			//west
			if (map [i][j].current_status == 1 && j > 0){
				if (WEST == 1){
					life_count++;
				}
			}	
			else if (map [i][j].current_status == 0 && j > 0){
				if (WEST == 1){
					dead_count++;
				}
			}				
			//northeast
			if (map [i][j].current_status == 1 && i > 0 && j < COLUMNS){
				if (NORTHEAST == 1){
					life_count++;
				}
			}
			else if (map [i][j].current_status == 0 && i > 0 && j < COLUMNS){
				if (NORTHEAST == 1){
					dead_count++;
				}
			}
			//southeast
			if (map [i][j].current_status == 1 && i < ROWS && j < COLUMNS){
				if (SOUTHEAST == 1){
					life_count++;
				}	
			}
			else if (map [i][j].current_status == 0 && i < ROWS && j < COLUMNS){
				if (SOUTHEAST == 1){
					dead_count++;
				}	
			}
			//northwest
			if (map [i][j].current_status == 1 && i > 0 && j > 0){
				if (NORTHWEST == 1){
					life_count++;
				}
			}
			else if (map [i][j].current_status == 0 && i > 0 && j > 0){
				if (NORTHWEST == 1){
					dead_count++;
				}
			}
			//southwest
			if (map [i][j].current_status == 1 && i < ROWS && j > 0){
				if (SOUTHWEST == 1){
					life_count++;
				}
			}
			else if (map [i][j].current_status == 0 && i < ROWS && j > 0){
				if (SOUTHWEST == 1){
					dead_count++;
				}
			}
			
			//determine if cell lives, dies or a new one borns, update to second layer of map
			if (life_count < UNDERPOPULATION_LIMIT){
				map[i][j].future_status = 0;
			}
			else if (life_count >= LIVE_MIN && life_count <= LIVE_MAX){
				map[i][j].future_status = 1;
			}
			else if (life_count > OVERPOPULATION_LIMIT){
				map[i][j].future_status = 0;	
			}
			
			if (dead_count == REBIRTH_LIMIT){
				map[i][j].future_status = 1;
			}
			
			//reset counters for next cell
			life_count = 0;
			dead_count = 0;
		}
	}
	print_count (creature_count);
	//copies second, temporary layer of the map to the first one to be printed
	new_copy_map(map);
}
/*********************************************************************
;	F U N C T I O N    D E S C R I P T I O N
;---------------------------------------------------------------------
; NAME: copy_map
; DESCRIPTION: Copies the second layer of the array to the first one, second layer acts as a temp
;	Input: Array
;	Output: None
;  Used global variables:
; REMARKS when using this function:
;*********************************************************************/
void new_copy_map (struct cell_info map[ROWS][COLUMNS]){
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
; NAME: debug_print
; DESCRIPTION: Allows easier debugging by disabling ncurses and printing map to console
;	Input: Array
;	Output: None
;  Used global variables:
; REMARKS when using this function:
;*********************************************************************/
void debug_print (struct cell_info map[ROWS][COLUMNS]){
	int i, j;
	
	for (i = 0; i < ROWS; i++){
		for (j = 0; j < COLUMNS; j++){
			printf ("%d", map[i][j].current_status);
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
	
	if (DEBUG_MODE == 1){
		printf("Current iteration: %d \n", iteration);
	}
	else {
		init_pair(1, COLOR_RED, COLOR_BLACK);
		init_pair(2, COLOR_RED, COLOR_BLUE);
		init_pair(3, COLOR_RED, COLOR_GREEN);
		
		attron(COLOR_PAIR(1));
		mvprintw(ROWS + 3, 1, "Current iteration: %d", iteration);
		attroff(COLOR_PAIR(1));	
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
	
	if (DEBUG_MODE == 1){
		printf("Creature count: %d \n", creature_count);
	}
	else {
		init_pair(1, COLOR_RED, COLOR_BLACK);
		init_pair(2, COLOR_RED, COLOR_BLUE);
		init_pair(3, COLOR_RED, COLOR_GREEN);
		
		attron(COLOR_PAIR(1));
		mvprintw(ROWS + 4, 1, "Creature count: %d \n", creature_count);
		attroff(COLOR_PAIR(1));	
	}
}
/*********************************************************************
;	F U N C T I O N    D E S C R I P T I O N
;---------------------------------------------------------------------
; NAME: map_reader
; DESCRIPTION:
;	Input:
;	Output:
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
			map[i][j].snake_direction = 0;
		}
	} 
	fclose(myFile);
}
/*********************************************************************
;	F U N C T I O N    D E S C R I P T I O N
;---------------------------------------------------------------------
; NAME: menu_function
; DESCRIPTION: Show menu to operate the simulation
;	Input: None
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
; NAME:
; DESCRIPTION:
;	Input:
;	Output:
;  Used global variables:
; REMARKS when using this function:
;*********************************************************************/
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