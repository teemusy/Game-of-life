/*compile with -lncurses option*/

/*-------------------------------------------------------------------*
*    HEADER FILES                                                    *
*--------------------------------------------------------------------*/
#include <curses.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <cstdlib>

#include "constants.h"
#include "functions.h"
#include "snake.h"


/*********************************************************************
*    MAIN PROGRAM                                                      *
**********************************************************************/

//TODO
//-options that don't halt the game
//-magic numbers
//-streamline update_life function
//-snake age?
//-store snake class map as pointer
//-fix randomly occuring segmentation when randomizing map, seems to be function.cpp row 332
//-combine status message functions

int main() {
	
	int random_value, iteration, i, menu_choice;
	float game_speed;
	struct cell_info new_map[ROWS][COLUMNS];
	
	//snake init 
	Snake testi;
	
	srand(time(NULL)); //Randomize seed initialization for map_fill
	iteration = 0;
	game_speed = TIME_BETWEEN_REBIRTH;
	
	//check if debug mode is on, else init ncurses
	#ifdef DEBUG_MODE
		map_filler(new_map);
		testi.set_head_location(new_map, 10,10);
		while(true){
			testi.update_snake(new_map);
			update_life (new_map);
			debug_print (new_map);
			print_stats(iteration);
			iteration++;
			sleep_for_seconds(game_speed);
			std::system("clear");
		}

	#else
	
		initscr(); //ncurses init
		curs_set(0);
		start_color();
		
		//init windows, size y, size x, location y, location x
		WINDOW* map_window = newwin(ROWS + 2, COLUMNS + 2, 0, 0);
		WINDOW* text_window = newwin(5, COLUMNS + 2, ROWS+2, 0);
		//WINDOW* menu_window = newwin(ROWS + 2, 20, 0, COLUMNS+2);
		
		//draws borders
		box(text_window,0,0);
		//box(menu_window,0,0);
		
		//run menu
		menu_choice = menu_function(map_window, &game_speed);
		draw_static (map_window); 
		switch(menu_choice){
			case 0:
				map_filler(new_map);
				break;
			case 1:
				map_reader (new_map);
				break;
			default:
				map_filler (new_map);	
				break;
		}
		testi.set_head_location(new_map, 10,10);
		
		//MAIN LOOP
		while(true){
		
			print_stats(iteration);
			iteration++;
			testi.update_snake(new_map);
			update_life (new_map);
			draw_creatures (new_map, map_window);
			refresh();
			wrefresh(map_window);
			wrefresh(text_window);
			//wrefresh(menu_window);
			sleep_for_seconds(game_speed);
		}
		endwin();
		
	#endif
	return 0;
	
}/* end of main */

