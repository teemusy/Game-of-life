/*-------------------------------------------------------------------*
*    GLOBAL VARIABLES                                                *
*--------------------------------------------------------------------*/
/* Control flags */
/* Global constants */
//determines the size of the map
#define ROWS 50
#define COLUMNS 100
#define TIME_BETWEEN_REBIRTH 0.2
//to determine initial seed
#define FILL_PERCENTAGE 30
//define directions
#define NORTH map [i-1][j].current_status
#define SOUTH map [i+1][j].current_status
#define EAST map [i][j+1].current_status
#define WEST map [i][j-1].current_status
#define NORTHEAST map [i-1][j+1].current_status
#define SOUTHEAST map [i+1][j+1].current_status
#define NORTHWEST map [i-1][j-1].current_status
#define SOUTHWEST map [i+1][j-1].current_status
//define game rules
#define UNDERPOPULATION_LIMIT 2
#define LIVE_MIN 2
#define LIVE_MAX 3
#define OVERPOPULATION_LIMIT 3
#define REBIRTH_LIMIT 3
#define SNAKE_MAX_LEN 10

/* Global variables */
/* Global structures */
struct cell_info {
	   int current_status;
	   int future_status;
	   int snake_head;
	   int snake_direction;
};