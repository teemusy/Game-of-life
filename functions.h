#include <curses.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>

/*-------------------------------------------------------------------*
*    FUNCTION PROTOTYPES                                             *
*--------------------------------------------------------------------*/

/** 
* \fn int random_value_filler ()
* \brief Returns randomly either 1 or 0 as integer
* \return 1 or 0
*/
int random_value_filler ();

/** 
* \fn void map_filler (struct cell_info map[ROWS][COLUMNS])
* \brief Fills the map struct current_status randomly with 1 or 0 and put's 0's to other struct fields
* \param Struct to fill
* \return None
*/
void map_filler (struct cell_info map[ROWS][COLUMNS]);

/** 
* \fn void draw_static (WINDOW *local_win)
* \brief Draws borders around the map window
* \param Ncurses window as pointer
* \return None
*/
void draw_static (WINDOW *local_win);

/** 
* \fn void draw_creatures (struct cell_info map[ROWS][COLUMNS], WINDOW *local_win)
* \brief Draws simulation on the map window
* \param Map struct to read map info and ncurses window as pointer
* \return None
*/
void draw_creatures (struct cell_info map[ROWS][COLUMNS], WINDOW *local_win);

/** 
* \fn void sleep_for_seconds (float s)
* \brief Sleeps for given amount of time
* \param Time to sleep in seconds as float
* \return None
*/
void sleep_for_seconds (float s);

/** 
* \fn void copy_map (struct cell_info map[ROWS][COLUMNS])
* \brief Copies simulations future status to current status
* \param Struct to read and write info to
* \return None
*/
void copy_map (struct cell_info map[ROWS][COLUMNS]);

/** 
* \fn void update_life (struct cell_info map[ROWS][COLUMNS])
* \brief Determines if cells live, die or born again
* \param Struct to read map info
* \return None
*/
void update_life (struct cell_info map[ROWS][COLUMNS]);

/** 
* \fn void debug_print (struct cell_info map[ROWS][COLUMNS])
* \brief Allows easier debugging by disabling ncurses and printing map to console
* \param Struct to read map info
* \return None
*/
void debug_print (struct cell_info map[ROWS][COLUMNS]);


/** 
* \fn void print_stats (int iteration, float *speed)
* \brief Updates statistics on screen
* \param Current iteration as integer and game speed float as pointer
* \return None
*/
void print_stats (int iteration, float *speed);

/** 
* \fn void print_count (int creature_count)
* \brief Updates count on screen, should combine with print_stats function
* \param Creature count as integer
* \return None
*/
void print_count (int creature_count);

/** 
* \fn void map_reader(struct cell_info map[ROWS][COLUMNS], int map_choice)
* \brief Struct to store map info, choice of savefile
* \param Map struct to save map info and map_choice integer to choose which map to read
* \return None
*/
void map_reader(struct cell_info map[ROWS][COLUMNS], int map_choice);

/** 
* \fn void map_saver(struct cell_info map[ROWS][COLUMNS])
* \brief Saves current map status to file
* \param Map struct to read map info from
* \return None
*/
void map_saver(struct cell_info map[ROWS][COLUMNS]);

/** 
* \fn int menu_function(WINDOW *local_win, float *speed)
* \brief Main menu for the simulation
* \param Ncurses window as pointed, game speed float as pointer
* \return none
*/
int menu_function(WINDOW *local_win, float *speed);

/** 
* \fn int random_direction ()
* \brief Gives 4 different random directions for the snake
* \param None
* \return Direction as integer
*/
int random_direction ();

/** 
* \fn void array_shift(int arr[2][SNAKE_MAX_LEN], int len, int dir)
* \brief Shifts [2][x] array x-cells left or right
* \param 2D array, size of x as integer, direction 1/-1 as integer
* \return None
*/
void array_shift(int arr[2][SNAKE_MAX_LEN], int len, int dir);