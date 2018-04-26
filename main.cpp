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
//-magic numbers
//-streamline update_life function
//-snake age?
//-store snake class map as pointer inside the object
//-0,0 seems to never spawn a creature
//-combine status message functions
//-clean up the code for options during the game
//-pause
//-printc count doesn't use window
//-snake loading and saving

int main() {
	
	int iteration; /**Keeps count of creature iteration */
	int	menu_choice; /** Keeps track of menu choice */
	int highlight; /** Highlights menu choice */
	int choice; /** Chosen menu choice */
	int pause; /** Keeps track of pause/resume*/
	float game_speed; /** Game update speed, smaller is faster */
	float old_speed; /** Keeps track of the old speed for the pause function */
	struct cell_info new_map[ROWS][COLUMNS]; /** Stores map and snake information */
	
	//snake init 
	Snake testi;
	
	srand(time(NULL)); //Randomize seed initialization for map_fill
	iteration = 0;
	pause = 0;
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
				map_reader (new_map, 1);
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
			const char *a[6];
			a[0] = "Randomize map";
			a[1] = "Save";
			a[2] = "Load";
			a[3] = "Load premade map";
			a[4] = "XXPause/resumeXX";
			a[5] = "XXReset snakeXX";

			//add length check
			int choice_len = 6;

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
						game_speed = game_speed + 0.05;
						if (game_speed > 10 && pause == 0){
							game_speed = 10;
						}
						mvwprintw(menu_window, ROWS-2, COLUMNS/4, "Rebirth speed is %.3f seconds.", game_speed);
						break;			
						
					case KEY_LEFT:
						game_speed = game_speed - 0.05;
						if (game_speed <= 0 && pause == 0){
							game_speed = 0.05;
						}
						mvwprintw(menu_window, ROWS-2, COLUMNS/4, "Rebirth speed is %.3f seconds.", game_speed);
						break;
						
					default:
						break;
				}
			
			//enter
			if(choice == 10){
				switch(menu_choice){
					//randomize
					case 0:
						map_filler(new_map);
						break;					
					//save
					case 1:
						map_saver (new_map);
						break;					
					//load
					case 2:
						map_reader (new_map, 2);
						break;					
					//premade
					case 3:
						map_reader (new_map, 1);
						break;
					//pause/resume
					case 4:
						//not working as intended
						/*
						if (pause == 0){
							old_speed = game_speed;
							//not true pause but close enough
							game_speed = 999999;
							pause = 1;
						}
						else {
							game_speed = old_speed;
							pause = 0;
						}
						*/
						break;					
					//reset snake
					case 5:
						//destroy old snake, create new snake with randomized values
						//testi.delete_snake();
						//Snake testi;						
						//testi.set_head_location(new_map, 10,10);
						break;
					default:
						break;
					
				}
			}
			
			print_stats(iteration, &game_speed);
			iteration++;
			testi.update_snake(new_map);
			update_life (new_map);
			draw_creatures (new_map, map_window);
			refresh();
			wrefresh(map_window);
			wrefresh(text_window);
			wrefresh(menu_window);
			sleep_for_seconds(game_speed);
		}
		endwin();
		
	#endif
	return 0;
	
}/* end of main */

