#ifndef __STRUCT_H__
#define __STRUCT_H__
#include "const.h"

/* Structure allowing to record if a touch of the keyboard was rested */
typedef struct {
	char key[SDLK_LAST] ;
	int quit ;
}input_t;

/* Structure of initialization of the screen */
typedef struct {
	SDL_Surface * screen ;
	SDL_Surface * launcher ;
	SDL_Surface * frame ;
	unsigned int currentOrientation ;
}init_t;

/* Structure of access to the positions of bubbles and to their display */
typedef struct {
	SDL_Surface * bub_colors[NUM_COLORS] ; /* Will store the various images of bubbles in different cells */
	int * * bub_array ; 		   /* Inform about the positions and the colors of bubbles displayed on the game board */
	int * * * bub_center ;		   /* Will store the coordinates of the center of bubbles
									* First cell is for the abscissa .x *
									* Second one is for the ordinate .y */
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

	/* Corresponds to the image of the launcher when we press on space to launch the bubble */
	unsigned int currentOrientation ;

}bubble_t ;

#endif