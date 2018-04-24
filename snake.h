#include "functions.h"

class Snake{
	private:
		int i;
		int snake_alive;
		int hatching_time;
		int snake_length;
		int snake_head_var[2];
		int snake_old_head_var[2];	
		int last_dir;
		int snake_location[2][SNAKE_MAX_LEN];
		int n, e, s, w;
		void lay_egg (struct cell_info map[ROWS][COLUMNS], int loc_x, int loc_y);
		void hatch_egg (struct cell_info map[ROWS][COLUMNS]);
		void move_snake (struct cell_info map[ROWS][COLUMNS]);
		void destroy_snake (struct cell_info map[ROWS][COLUMNS]);
		//void delete_snake ();
	
	public:
		void set_head_location (struct cell_info map[ROWS][COLUMNS], int loc_x, int loc_y);
		void update_snake (struct cell_info map[ROWS][COLUMNS]);
		~Snake();
};