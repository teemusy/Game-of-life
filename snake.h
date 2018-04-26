#include "functions.h"

/*! \class Snake snake.h "snake.h"
 *  \Keeps track of snake movement, length and life
 */
class Snake{
	private:
		int i;
		int snake_alive; /** Is snake alive */
		int hatching_time; /** Keeps count of hatching time*/
		int snake_length; /** Snake length*/
		int snake_head_var[2]; /** Location of snake head*/
		int snake_old_head_var[2]; /** Old location of snake head*/
		int last_dir; /** Last direction of the snake*/
		int snake_location[2][SNAKE_MAX_LEN]; /** Snake location*/
		int n, e, s, w; /** Keeps count if snake has tried all directions and failed which means that the snake has knotted itself and has to be destroyed*/
		void lay_egg (struct cell_info map[ROWS][COLUMNS], int loc_x, int loc_y); /** Creates egg on location*/
		void hatch_egg (struct cell_info map[ROWS][COLUMNS]); /** Checks if egg is ready to hatch*/
		void move_snake (struct cell_info map[ROWS][COLUMNS]); /** Moves snake*/
		void destroy_snake (struct cell_info map[ROWS][COLUMNS]); /** Destroys snake*/
		//void delete_snake ();
	
	public:
		void set_head_location (struct cell_info map[ROWS][COLUMNS], int loc_x, int loc_y); /** Allows snake to be put on given location*/
		void update_snake (struct cell_info map[ROWS][COLUMNS]); /** Updates snake movement or egg hatching*/
		~Snake(); /** Object destructor*/
};