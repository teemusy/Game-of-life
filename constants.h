/*-------------------------------------------------------------------*
*    GLOBAL VARIABLES                                                *
*--------------------------------------------------------------------*/
/* Control flags */
/* Global constants */
//determines the size of the map
#define ROWS 50
#define COLUMNS 100
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

#define SNAKE_NORTH map [i-1][j].snake_head
#define SNAKE_SOUTH map [i+1][j].snake_head
#define SNAKE_EAST map [i][j+1].snake_head
#define SNAKE_WEST map [i][j-1].snake_head
#define SNAKE_NORTHEAST map [i-1][j+1].snake_head
#define SNAKE_SOUTHEAST map [i+1][j+1].snake_head
#define SNAKE_NORTHWEST map [i-1][j-1].snake_head
#define SNAKE_SOUTHWEST map [i+1][j-1].snake_head

#define SNAKE_BODY_NORTH map [i-1][j].snake_body
#define SNAKE_BODY_SOUTH map [i+1][j].snake_body
#define SNAKE_BODY_EAST map [i][j+1].snake_body
#define SNAKE_BODY_WEST map [i][j-1].snake_body
#define SNAKE_BODY_NORTHEAST map [i-1][j+1].snake_body
#define SNAKE_BODY_SOUTHEAST map [i+1][j+1].snake_body
#define SNAKE_BODY_NORTHWEST map [i-1][j-1].snake_body
#define SNAKE_BODY_SOUTHWEST map [i+1][j-1].snake_body

#define EGG_NORTH map [i-1][j].egg
#define EGG_SOUTH map [i+1][j].egg
#define EGG_EAST map [i][j+1].egg
#define EGG_WEST map [i][j-1].egg
#define EGG_NORTHEAST map [i-1][j+1].egg
#define EGG_SOUTHEAST map [i+1][j+1].egg
#define EGG_NORTHWEST map [i-1][j-1].egg
#define EGG_SOUTHWEST map [i+1][j-1].egg
//define game rules
#define UNDERPOPULATION_LIMIT 2
#define LIVE_MIN 2
#define LIVE_MAX 3
#define OVERPOPULATION_LIMIT 3
#define REBIRTH_LIMIT 3
#define SNAKE_MAX_LEN 10
#define TIME_TO_HATCH 20
#define TIME_BETWEEN_REBIRTH 0.5
/* Global variables */
/* Global structures */
/** Keeps track of cell status */
struct cell_info {
	   int current_status;
	   int future_status;
	   int snake_head;
	   int snake_body;
	   int egg;
};

//#define DEBUG_MODE