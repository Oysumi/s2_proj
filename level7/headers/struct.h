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

/* Specific structure corresponding to the bubbles that have to explode */
typedef struct {
	SDL_Rect * image ;
	SDL_Rect * position ;
	int bub_color ;
	int isExplosing ;
}explode_t;

/* Structure to access to the positions of bubbles */
typedef struct {
	SDL_Surface * bub_colors[NUM_COLORS] ; /* Will store the various images of bubbles in different cells */
	SDL_Surface * bub_explosion[NUM_COLORS] ; /* Will store the images of the bubbles exploding in defferent cells */

	int * * bub_array ; 		   		   /* Inform about the positions and the colors of bubbles displayed on the game board */

	int * * * bub_center ;		   		   /* Will store the coordinates of the center of bubbles
					    					* First cell is for the abscissa .x *
					    					* Second one is for the ordinate .y */

	int * * bub_connected_component	;	   /* Will allow to determine which bubbles it will be necessary to remove from the board */

	int * * bub_fifo ;					   /* Represent in reality a file which will help in the connectivity of bubbles */
	int head ;
	int tail ;
	
	explode_t * bub_falling ;
	int fall_head ;
	int nb_bubexplosions ;
	int nb_bubout ;
	int counter ;
					    
	unsigned int currentOrientation ; 	   /* Corresponds to the image of the current launcher */
}game_t;

/* Structure defining bubbles */
typedef struct {

	SDL_Surface * sprite ;
	SDL_Rect pos ;
	int rotation ; /* If the bubble is on the launcher and we move it to te left/right, then the bubble has a different 'angle' */

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

/* Allows to control the descent of the ceiling */
typedef struct {

	int state ; /* Represent in reality to which stage is situated the ceiling *
				 * (of 0 meaning that it did not come down ; in 11 yet where it touchs the ground) */

	SDL_Surface * image_ceiling ;
	SDL_Surface * image_chain ;
	SDL_Rect position ;

	int pos_x ;
	int pos_y ;

}ceiling_t ;

#endif
