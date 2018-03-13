/*-------------------------------------------------------------------*
*    HEADER FILES                                                    *
*--------------------------------------------------------------------*/
#include <iostream>
#include <cstdlib>

/*-------------------------------------------------------------------*
*    GLOBAL VARIABLES                                                *
*--------------------------------------------------------------------*/
/* Control flags */

/* Global constants */
const int ROWS = 10;
const int COLUMNS = 10;

/* Global variables */

/* Global structures */

/*-------------------------------------------------------------------*
*    FUNCTION PROTOTYPES                                             *
*--------------------------------------------------------------------*/

//fill map with 1 or 0
int random_value_filler ();
//fill map with random number
void map_filler ();

/*********************************************************************
*    MAIN PROGRAM                                                      *
**********************************************************************/

int main(void) {
	
	int map[ROWS][COLUMNS];
	int random_value;
	srand( time(NULL) ); //Randomize seed initialization
	

	//std::cout << random_value << "\n";   
	//std::cout << sizeof(map);   
	//map_filler ();
	
	
	int i, j;
	for(i = 0; i < ROWS; i++){
		
		//map[i][j] = random_value_filler ();
		//map[i][j] = 0;
		
		for(j = 0; j < COLUMNS; j++){
			
			//map[i][j] = 0;
		}
		j = 0;
	}
	
	
}/* end of main */

/*********************************************************************
*    FUNCTIONS                                                     *
**********************************************************************/

int random_value_filler (){
	int random_value;
		
	random_value = (rand() % 2);

	return random_value;
}

void map_filler (){
	int i, j;
	
	for(i = 0; i < ROWS; i++){
		
		//map[i][j] = random_value_filler ();
		//map[i][j] = 0;
		
		for(j = 0; j < COLUMNS; j++){
			
			//map[i][j] = 0;
		}
		j = 0;
	}
}

/*********************************************************************
;	F U N C T I O N    D E S C R I P T I O N
;---------------------------------------------------------------------
; NAME:
; DESCRIPTION:
;	Input:
;	Output:
;  Used global variables:
; REMARKS when using this function:
;*********************************************************************/
