/*-------------------------------------------------------------------*
*    HEADER FILES                                                    *
*--------------------------------------------------------------------*/
#include <stdio.h>
#include <curses.h>

/*-------------------------------------------------------------------*
*    GLOBAL VARIABLES                                                *
*--------------------------------------------------------------------*/
/* Control flags */

/* Global constants */
#define ROWS 10
#define COLUMNS 10
#define LAYERS 2
#define TIME_BETWEEN_REBIRTH 1
//for later use to determine initial seed, not in use atm
#define FILL_PERCENTAGE 70
//debug mode disables ncurses for easier debugging
#define DEBUG_MODE 1

/* Global variables */

/* Global structures */

/*-------------------------------------------------------------------*
*    FUNCTION PROTOTYPES                                             *
*--------------------------------------------------------------------*/

//fills both layers of map with 1 or 0
int random_value_filler ();
//fill map with random number
void map_filler (int map [ROWS][COLUMNS][LAYERS]);
//draw static stuff
void draw_static ();
//draw creatures with ncurses
void draw_creatures (int map [ROWS][COLUMNS][LAYERS]);
//sleep function
void sleep_for_seconds (float s);
//check if creature lives, dies or regenerates, then update map
void update_life (int map [ROWS][COLUMNS][LAYERS]);
//print function for debugging
void debug_print (int map [ROWS][COLUMNS][LAYERS]);

/*********************************************************************
*    MAIN PROGRAM                                                      *
**********************************************************************/

//TODO


int main(void) {
	
	int random_value;
	int map [ROWS][COLUMNS][LAYERS];
	
	srand( time(NULL) ); //Randomize seed initialization for map_fill
	map_filler (map); //fill map with random booleans
	
	if (DEBUG_MODE == 1){
		while(true){
			
			debug_print (map);
			sleep_for_seconds(TIME_BETWEEN_REBIRTH);
			update_life (map);
		}
	}
	else {
		//ncurses init
		initscr();
		curs_set(0);
		start_color();
		//draws borders
		draw_static (); 
		
		while(true){
			
			draw_creatures (map);
			sleep_for_seconds(TIME_BETWEEN_REBIRTH);
			update_life (map);

		}
		endwin();			/*End curses mode */
	}
	
	return 0;
	
}/* end of main */

/*********************************************************************
*    FUNCTIONS                                                     *
**********************************************************************/
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
	
	random_value = (rand() % 2);
	return random_value;
}
/*********************************************************************
;	F U N C T I O N    D E S C R I P T I O N
;---------------------------------------------------------------------
; NAME: map_filler
; DESCRIPTION: Fills map array with 1's or 0's
;	Input: Array
;	Output: None
;  Used global variables:
; REMARKS when using this function:
;*********************************************************************/
void map_filler (int map [ROWS][COLUMNS][LAYERS]){
	int i, j;
	
	for(i = 0; i < ROWS; i++){

		for(j = 0; j < COLUMNS; j++){
			map[i][j][1] = random_value_filler ();
			//useless to copy first layer, should remove?
			map[i][j][2] = map[i][j][1];
		}
		j = 0;
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
void draw_creatures (int map [ROWS][COLUMNS][LAYERS]){
	int i, j;
	
	//declare color pairs
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLUE);
	init_pair(3, COLOR_RED, COLOR_GREEN);
		
	//draw creatures
	attron(COLOR_PAIR(2));
	for(i = 0; i < ROWS; i++){
		
		for(j = 0; j < COLUMNS; j++){
			if (map[i][j][1] == 1){
				mvprintw(i+1, j+1, "@");
			}
			else{
				mvprintw(i+1, j+1, " ");
			}
		}
		j = 0;
	}
	attroff(COLOR_PAIR(2));	
	
	refresh();			/* Print it on to the real screen */
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
void draw_static (){
	int i;
	
	//declare color pairs
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLUE);
	init_pair(3, COLOR_RED, COLOR_GREEN);
	
	//draw horizontal borders
	attron(COLOR_PAIR(1));
	for(i = 0; i < COLUMNS + 2; i++){
		mvprintw(0, i, "@");
		mvprintw(ROWS + 1, i, "@");
	}
	//draw vertical borders
	for(i = 0; i < ROWS + 2; i++){
		mvprintw(i, 0, "@");
		mvprintw(i, COLUMNS + 1, "@");
	}
	attroff(COLOR_PAIR(1));	
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
; DESCRIPTION:
;	Input:
;	Output:
;  Used global variables:
; REMARKS when using this function:
;*********************************************************************/
void update_life (int map [ROWS][COLUMNS][LAYERS]) {
	
	int i, j, life_count, dead_count;
	
	
	for (i = 0; i < ROWS; i++){
		
		for (j = 0; j < COLUMNS; j++){
			//check if it's legal array value, eg. not -1
			//check if cell has life and if it's inside the array
			//check north
			if (map [i][j][1] == 1 && i > 0){
				if (map [i-1][j][1] == 1){
					life_count++;
				}
			}
			//south
			if (map [i][j][1] == 1 && i < ROWS){
				if (map [i+1][j][1] == 1){
					life_count++;
				}	
			}
			//east
			if (map [i][j][1] == 1 && j < COLUMNS){
				if (map [i][j+1][1] == 1){
					life_count++;
				}
			}
			//west
			if (map [i][j][1] == 1 && j > 0){
				if (map [i][j-1][1] == 1){
					life_count++;
				}
			}			
			//northeast
			if (map [i][j][1] == 1 && i > 0 && j < COLUMNS){
				if (map [i-1][j+1][1] == 1){
					life_count++;
				}
			}
			//southeast
			if (map [i][j][1] == 1 && i < ROWS && j < COLUMNS){
				if (map [i+1][j+1][1] == 1){
					life_count++;
				}	
			}
			//northwest
			if (map [i][j][1] == 1 && i > 0 && j > 0){
				if (map [i-1][j-1][1] == 1){
					life_count++;
				}
			}
			//southwest
			if (map [i][j][1] == 1 && i < ROWS && j > 0){
				if (map [i+1][j-1][1] == 1){
					life_count++;
				}
			}
			
			//else if could be replaced with else
		
		}
		j = 0;
		
	}
	printf("life_count: %d \t dead_count: %d \n\n", life_count, dead_count);
	life_count = 0;
	dead_count = 0;
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
void debug_print (int map [ROWS][COLUMNS][LAYERS]){
	
	int i, j;
	
	for (i = 0; i < ROWS; i++){
		for (j = 0; j < COLUMNS; j++){
			printf ("%d", map[i][j][1]);
		}
		j = 0;
		printf("\n");
	}
	printf("\n");
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
