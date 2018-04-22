#ifndef __STRUCT_H__
#define __STRUCT_H__
#include "const.h"

/* Structure allowing to record if a touch of the keyboard was rested */
typedef struct {
	char key[SDLK_LAST] ;
	int quit ;
}input_t;

/* Structure to initialize the screen */
typedef struct {
	SDL_Surface * screen ;
	SDL_Surface * launcher ;
	SDL_Surface * frame ;
}init_t;

/* Structure to access to the positions of bubbles */
typedef struct {
	SDL_Surface * bub_colors[NUM_COLORS] ; /* Will store the various images of bubbles in different cells */

	int * * bub_array ; 		   		   /* Inform about the positions and the colors of bubbles displayed on the game board */

	int * * * bub_center ;		   		   /* Will store the coordinates of the center of bubbles
					    					* First cell is for the abscissa .x *
					    					* Second one is for the ordinate .y */

	int * * bub_connected_component	;	   /* Will allow to determine which bubbles it will be necessary to remove from the board */

	int * * bub_fifo ;					   /* Represent in reality a file which will help in the connectivity of bubbles */
	int head ;
	int tail ;
					    
	unsigned int currentOrientation ; 	   /* Corresponds to the image of the current launcher */
}game_t;

/* Structure defining bubbles */
typedef struct {

	SDL_Surface * sprite ;
	SDL_Rect pos ;

	unsigned int color ;

	/* Real coordinates of the bubble increasing the precision during the movement */
	double x ;
	double y ;

	int launcher_x ; /* BUB_STARTX */
	int launcher_y ; /* BUB_STARTY */

	bool launched ;
	bool isMoving ;

	/* Step of movement */
	double dx ; 
	double dy ;

}bubble_t ;

/* Structure to control the speed of the launcher */
typedef struct {

	int previousTime ;
	int currentTime ;

}timecontrol_t ;

#endif
