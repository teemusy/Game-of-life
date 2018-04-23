#include <curses.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>

/*-------------------------------------------------------------------*
*    FUNCTION PROTOTYPES                                             *
*--------------------------------------------------------------------*/

//fills both layers of map with 1 or 0
int random_value_filler ();
//fill map with random number
void map_filler (struct cell_info map[ROWS][COLUMNS]);
//draw static stuff
void draw_static (WINDOW *local_win);
//draw creatures with ncurses
void draw_creatures (struct cell_info map[ROWS][COLUMNS], WINDOW *local_win);
//sleep function
void sleep_for_seconds (float s);
void copy_map (struct cell_info map[ROWS][COLUMNS]);
//check if creature lives, dies or regenerates, then update map
void update_life (struct cell_info map[ROWS][COLUMNS]);
//print function for debugging
void debug_print (struct cell_info map[ROWS][COLUMNS]);
//copy array layer
void copy_map (struct cell_info map[ROWS][COLUMNS]);
//print statistics
void print_stats (int iteration);
void print_count (int creature_count);
void map_reader(struct cell_info map[ROWS][COLUMNS]);
int menu_function(WINDOW *local_win, float *speed);
int random_direction ();
int options(WINDOW *local_win, float *speed, int choice);
void array_shift(int arr[2][SNAKE_MAX_LEN], int len, int dir);