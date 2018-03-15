/*-------------------------------------------------------------------*
*    HEADER FILES                                                    *
*--------------------------------------------------------------------*/
#include <stdio.h>
//#include <cstdlib>
#include <curses.h>
#include <time.h>
#include <unistd.h>

/*-------------------------------------------------------------------*
*    GLOBAL VARIABLES                                                *
*--------------------------------------------------------------------*/
/* Control flags */

/* Global constants */
const int ROWS = 40;
const int COLUMNS = 100;

/* Global variables */

/* Global structures */

/*-------------------------------------------------------------------*
*    FUNCTION PROTOTYPES                                             *
*--------------------------------------------------------------------*/

//fill map with 1 or 0
int random_value_filler ();
//fill map with random number
void map_filler (int map[ROWS][COLUMNS]);
//draw static stuff
void draw_static ();
//draw creatures with ncurses
void draw_creatures (int map [ROWS][COLUMNS]);

//testing looping function, not in use atm
void loop (int map [ROWS][COLUMNS]);

//testing sleep
void Sleep (float s);

/*********************************************************************
*    MAIN PROGRAM                                                      *
**********************************************************************/

int main(void) {
	
	//declare variables
	int random_value;
	int map[ROWS][COLUMNS];
	
	//temp check for input, c == 27 == esc
	//char c;
	
	srand( time(NULL) ); //Randomize seed initialization for map_fill
	
	//ncurses init
	initscr();
	curs_set(0);
	start_color();
	
	//map init
	 
	draw_static (); //draw static stuff */
	
	//testing update function
	
	//miksei päivity automaattisesti ja paras tapa painottaa tiettyä arvoa
	while(true)
    {
		
		Sleep(1);
		//fill map with 1's and 0's
		map_filler (map);
		//draw creatures
		draw_creatures (map);

		/*c=getch();
        if (c==27)
			break;*/
    }


	endwin();			//End curses mode		  */
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

void map_filler (int map [ROWS][COLUMNS]){
	int i, j;
	
	for(i = 0; i < ROWS; i++){
		map[i][j] = random_value_filler ();
		
		for(j = 0; j < COLUMNS; j++){
			map[i][j] = random_value_filler ();
		}
		j = 0;
	}
}

void draw_creatures (int map [ROWS][COLUMNS]){
	int i, j;
	
	//declare color pairs
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLUE);
	init_pair(3, COLOR_RED, COLOR_GREEN);
		
	//draw creatures
	attron(COLOR_PAIR(2));
	for(i = 0; i < ROWS; i++){
		
		for(j = 0; j < COLUMNS; j++){
			if (map[i][j] == 1){
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

void loop (int map [ROWS][COLUMNS]){
	

}

void Sleep (float s){ 

    int sec = s*1000000; 
    usleep(sec); 
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
