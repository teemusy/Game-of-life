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
//for later use to determine initial seed, not in use atm
#define FILL_PERCENTAGE 70

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
//-add second layer to map for temp use or use second array for it

int main(void) {
	
	//declare variables
	int random_value;
	int map [ROWS][COLUMNS][LAYERS];
	
	//temp check for input, c == 27 == esc
	//char c;
	
	srand( time(NULL) ); //Randomize seed initialization for map_fill
	
	//ncurses init
	/*initscr();
	curs_set(0);
	start_color();
	
	draw_static (); 
	*/
	
	/*draw static stuff */
	//fill map with random booleans
	map_filler (map);
	
	
	
	while(true)
    {
		
		sleep_for_seconds(1);
		//fill map with 1's and 0's
		debug_print (map);
		//draw creatures
		update_life (map);
		//draw_creatures (map);

		//c=getch();
        //if (c==27)
		//	break;
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

void sleep_for_seconds (float s){ 

    int sec = s*1000000; 
    usleep(sec); 
} 

void update_life (int map [ROWS][COLUMNS][LAYERS]) {
	
	int i, j, life_count, dead_count;
	
	
	for (i = 0; i < ROWS; i++){
		
		for (j = 0; j < COLUMNS; j++){
			//check north
			//check if it's legal array value, eg. not -1
			if (i > 0){
				
				
			}
			
		}
		j = 0;
		
	}
	

}

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
