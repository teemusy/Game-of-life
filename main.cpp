/*compile with -lncurses option*/

/*-------------------------------------------------------------------*
*    HEADER FILES                                                    *
*--------------------------------------------------------------------*/
#include <curses.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>

#include "constants.h"
#include "functions.h"
#include "snake.h"


/*********************************************************************
*    MAIN PROGRAM                                                      *
**********************************************************************/

//TODO
//-pause function
//-move cmd line input to function
//-magic numbers
//-streamline update_life function
//working snake

int main(int argc, char *argv[]) {
	
	int random_value, iteration, size_x, size_y, i, menu_choice;
	char cmd_line_input[50];
	float game_speed;
	struct cell_info new_map[ROWS][COLUMNS];
	
	//snake init 
	Snake testi;
	testi.set_head_location(20,20);
		
	srand( time(NULL) ); //Randomize seed initialization for map_fill
	iteration = 0;
	game_speed = TIME_BETWEEN_REBIRTH;
	

	
	//check if debug mode is on, else init ncurses
	#ifdef DEBUG_MODE
		map_filler(new_map);
		while(true){
			debug_print (new_map);
			//print iteration
			print_stats(iteration);
			iteration++;
			sleep_for_seconds(game_speed);
			//update_life (map);
		}

	#else
	
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
				map_filler(new_map);
				break;
			case 1:
				map_reader (new_map);
				break;
			default:
				map_filler (new_map);
				break;
		}
		
		//MAIN LOOP
		while(true){
			//options(menu_window, &game_speed);

			//draw_creatures (map, map_window);
			draw_creatures (new_map, map_window);
			//print iteration
			print_stats(iteration);
			refresh();
			wrefresh(map_window);
			wrefresh(text_window);
			wrefresh(menu_window);
			iteration++;
			sleep_for_seconds(game_speed);
			//update_life (map);
			update_life (new_map);
			testi.move_snake(new_map);
		}
		endwin(); /*End curses mode */
	#endif
	return 0;
	
}/* end of main */

