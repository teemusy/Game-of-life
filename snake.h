#include "functions.h"

class Snake{
	private:
		int snake_length;
		//[0][0] is head
		int snake_location[SNAKE_MAX_LEN][2];
	
	public:
		void set_head_location (int loc_x, int loc_y);
		void move_snake (struct cell_info map[ROWS][COLUMNS]);
		~Snake();
};