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

//TODO && IMPROVEMENTS
//-options that don't halt the game
//-magic numbers
//-streamline update_life function
//-snake age?
//-store snake class map as pointer
//-0,0 seems to never spawn a creature
//-combine status message functions
//-clean up the code for options during the game

int main() {
	
	int iteration, menu_choice, highlight, choice;
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
		WINDOW* menu_window = newwin(ROWS + 2, 20, 0, COLUMNS+2);
		
		//draws borders
		box(text_window,0,0);
		box(menu_window,0,0);
		
		nodelay(stdscr, TRUE);
		
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
		
		highlight = 0;
		//MAIN LOOP
		while(true){
			
			
			
			//menu choices
			const char *a[5];
			a[0] = "Randomize map";
			a[1] = "Load map.txt";
			a[2] = "Add snake";
			a[3] = "Remove snake";
			a[4] = "Pause/resume";

			//add length check
			int choice_len = 5;

			keypad(menu_window, true);
			nodelay(menu_window, true);
				int i;
				//add length of choices to for loop
				for (i = 0; i < choice_len; i++){
					if (i == highlight){
						wattron(menu_window, A_REVERSE);
						mvwprintw(menu_window, i+1, 1, "%s", a[i]);
						wattroff(menu_window, A_REVERSE);
						menu_choice = i;
					}
					else {
						mvwprintw(menu_window, i+1, 1, "%s", a[i]);
					}
				}
			
			choice = wgetch(menu_window);
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
						game_speed = game_speed + 0.005;
						if (game_speed > 10){
							game_speed = 10;
						}
						mvwprintw(menu_window, ROWS-2, COLUMNS/4, "Rebirth speed is %.3f seconds.", game_speed);
						break;			
						
					case KEY_LEFT:
						game_speed = game_speed - 0.005;
						if (game_speed <= 0){
							game_speed = 0.01;
						}
						mvwprintw(menu_window, ROWS-2, COLUMNS/4, "Rebirth speed is %.3f seconds.", game_speed);
						break;
						
					default:
						break;
				}
			
			//enter
			if(choice == 10){
				menu_choice = choice;	
			}
			
			print_stats(iteration, &game_speed);
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

