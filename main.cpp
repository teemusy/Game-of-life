/*-------------------------------------------------------------------*
*    HEADER FILES                                                    *
*--------------------------------------------------------------------*/
#include <iostream>
#include <cstdlib>
#include <curses.h>

/*-------------------------------------------------------------------*
*    GLOBAL VARIABLES                                                *
*--------------------------------------------------------------------*/
/* Control flags */

/* Global constants */
const int ROWS = 10;
const int COLUMNS = 10;

/* Global variables */
int map[ROWS][COLUMNS];
/* Global structures */

/*-------------------------------------------------------------------*
*    FUNCTION PROTOTYPES                                             *
*--------------------------------------------------------------------*/

//fill map with 1 or 0
int random_value_filler ();
//fill map with random number, not use atm
void map_filler ();
//draw map with ncurses
void draw_map ();

/*********************************************************************
*    MAIN PROGRAM                                                      *
**********************************************************************/

int main(void) {
	
	//declare variables
	
	int random_value;
	
	srand( time(NULL) ); //Randomize seed initialization
	
	//ncurses initialization
	initscr();
	curs_set(0);
	start_color();
	
	//fill map with 1's and 0's
	int i, j;
	for(i = 0; i < ROWS; i++){
		map[i][j] = random_value_filler ();
		
		for(j = 0; j < COLUMNS; j++){
			map[i][j] = random_value_filler ();
		}
		j = 0;
	}
	

	
	draw_map ();
	endwin();			/* End curses mode		  */
	return 0;
	
}/* end of main */

/*********************************************************************
*    FUNCTIONS                                                     *
**********************************************************************/

int random_value_filler (){
	int random_value;
	
	random_value = (rand() % 2);
	return random_value;
}

void map_filler (){
	int i, j;
	
	for(i = 0; i < ROWS; i++){
		
		//map[i][j] = random_value_filler ();
		//map[i][j] = 0;
		
		for(j = 0; j < COLUMNS; j++){
			
			//map[i][j] = 0;
		}
		j = 0;
	}
}

void draw_map (){
	
	int i, j;
	
	//declare color pairs
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLUE);
	init_pair(3, COLOR_RED, COLOR_GREEN);
	
	//draw borders
	attron(COLOR_PAIR(1));
	for(i = 0; i < 12; i++){
		mvprintw(0, i, "@");
		mvprintw(i, 0, "@");
		mvprintw(11, i, "@");
		mvprintw(i, 11, "@");
	}
	attroff(COLOR_PAIR(1));	
	
	//draw creatures
	
	attron(COLOR_PAIR(2));
	for(i = 0; i < ROWS; i++){
		
		for(j = 0; j < COLUMNS; j++){
			if (map[i][j] == 1){
			mvprintw(i+1, j+1, "@");
			}
		}
		j = 0;
	}
	attroff(COLOR_PAIR(2));	
	
	
	
	refresh();			/* Print it on to the real screen */
	getch();
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
