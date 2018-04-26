/*-------------------------------------------------------------------*
*    GLOBAL VARIABLES                                                *
*--------------------------------------------------------------------*/
/* Control flags */
/* Global constants */
/** Size of the map in y-direction */
#define ROWS 50
/** Size of the map in x-direction */
#define COLUMNS 100
/** Random fill percentage when generating random map */
#define FILL_PERCENTAGE 30

//define directions
/** Defines north direction for current.status*/
#define NORTH map [i-1][j].current_status
/** Defines south direction for current.status*/
#define SOUTH map [i+1][j].current_status
/** Defines east direction for current.status*/
#define EAST map [i][j+1].current_status
/** Defines west direction for current.status*/
#define WEST map [i][j-1].current_status
/** Defines northeast direction for current.status*/
#define NORTHEAST map [i-1][j+1].current_status
/** Defines southeast direction for current.status*/
#define SOUTHEAST map [i+1][j+1].current_status
/** Defines northwest direction for current.status*/
#define NORTHWEST map [i-1][j-1].current_status
/** Defines southwest direction for current.status*/
#define SOUTHWEST map [i+1][j-1].current_status

/** Defines north direction for snake_head*/
#define SNAKE_NORTH map [i-1][j].snake_head
/** Defines south direction for snake_head*/
#define SNAKE_SOUTH map [i+1][j].snake_head
/** Defines east direction for snake_head*/
#define SNAKE_EAST map [i][j+1].snake_head
/** Defines west direction for snake_head*/
#define SNAKE_WEST map [i][j-1].snake_head
/** Defines northeast direction for snake_head*/
#define SNAKE_NORTHEAST map [i-1][j+1].snake_head
/** Defines southeast direction for snake_head*/
#define SNAKE_SOUTHEAST map [i+1][j+1].snake_head
/** Defines northwest direction for snake_head*/
#define SNAKE_NORTHWEST map [i-1][j-1].snake_head
/** Defines southwest direction for snake_head*/
#define SNAKE_SOUTHWEST map [i+1][j-1].snake_head

/** Defines north direction for snake_body*/
#define SNAKE_BODY_NORTH map [i-1][j].snake_body
/** Defines south direction for snake_body*/
#define SNAKE_BODY_SOUTH map [i+1][j].snake_body
/** Defines east direction for snake_body*/
#define SNAKE_BODY_EAST map [i][j+1].snake_body
/** Defines west direction for snake_body*/
#define SNAKE_BODY_WEST map [i][j-1].snake_body
/** Defines northeast direction for snake_body*/
#define SNAKE_BODY_NORTHEAST map [i-1][j+1].snake_body
/** Defines southeast direction for snake_body*/
#define SNAKE_BODY_SOUTHEAST map [i+1][j+1].snake_body
/** Defines northwest direction for snake_body*/
#define SNAKE_BODY_NORTHWEST map [i-1][j-1].snake_body
/** Defines southwest direction for snake_body*/
#define SNAKE_BODY_SOUTHWEST map [i+1][j-1].snake_body

/** Defines north direction for egg*/
#define EGG_NORTH map [i-1][j].egg
/** Defines south direction for egg*/
#define EGG_SOUTH map [i+1][j].egg
/** Defines east direction for egg*/
#define EGG_EAST map [i][j+1].egg
/** Defines west direction for egg*/
#define EGG_WEST map [i][j-1].egg
/** Defines northeast direction for egg*/
#define EGG_NORTHEAST map [i-1][j+1].egg
/** Defines southeast direction for egg*/
#define EGG_SOUTHEAST map [i+1][j+1].egg
/** Defines northwest direction for egg*/
#define EGG_NORTHWEST map [i-1][j-1].egg
/** Defines southwest direction for egg*/
#define EGG_SOUTHWEST map [i+1][j-1].egg

//define game rules
/** Kills creature if there's less neighbours than the limit*/
#define UNDERPOPULATION_LIMIT 2
/** Kills creature if there's more neighbours than the limit*/
#define OVERPOPULATION_LIMIT 3
/** How many empty cells there has to be for a new creature to born*/
#define REBIRTH_LIMIT 3
/** Maximum length for the snake*/
#define SNAKE_MAX_LEN 6
/** Snake egg hatching time*/
#define TIME_TO_HATCH 20
/** Default simulation speed*/
#define TIME_BETWEEN_REBIRTH 0.5
/* Global variables */
/* Global structures */

/** 
* \struct cell_info
* \param current_status Tells if there's life in the cell
* \param future_status Tells the status for the cell in next iteration
* \param snake_head Tells if there's snake head in the cell
* \param snake_body Tells if there's snake body in the cell
* \param egg Tells if there's egg in the cell
* \brief This struct is used to store invidual cell info
*/
struct cell_info {
	   int current_status;
	   int future_status;
	   int snake_head;
	   int snake_body;
	   int egg;
};

//#define DEBUG_MODE