#include "functions.h"

class Snake{
	private:
		int i;
		int snake_length;
		int snake_head_var[2];
		int snake_old_head_var[2];	
		int last_dir;
		int snake_location[2][SNAKE_MAX_LEN];
		int n, e, s, w;
	
	public:
		void set_head_location (struct cell_info map[ROWS][COLUMNS], int loc_x, int loc_y);
		void move_snake (struct cell_info map[ROWS][COLUMNS]);
		void update_snake (struct cell_info map[ROWS][COLUMNS]);
		void lay_egg (struct cell_info map[ROWS][COLUMNS]);
		~Snake();
};