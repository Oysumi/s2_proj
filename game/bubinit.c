#ifndef __BUBINIT_C__
#define __BUBINIT_C__

#include "../headers/struct.h"
#include "../headers/init.h"
#include "../headers/bubble.h"
#include "../headers/const.h"
#include "SDL.h"

/* Fills the different cells of the array with zeros */
void bubarray_reset ( game_t * game )
{

	unsigned int i, j ; /* Used for a loop */
	int nb_bubx ;

	for ( i = 0 ; i < BUB_NY ; i++ )
	{
		game->bub_array[i] = ( int * ) malloc ( BUB_NX * sizeof ( int ) ) ;

		/* The number of bubbles depends on lines 
		 * Indeed we can place 8 bubbles on the even lines while we can place only 7 bubbles for the odd lines */
		nb_bubx = ( i % 2 == 0 ) ? BUB_NX : BUB_NX - 1 ;

		for ( j = 0 ; j < nb_bubx ; j++ )
		{
			game->bub_array[i][j] = 0 ;
		}

	}
}

void bubarray_initcenters ( game_t * game )
{
	SDL_Rect * tempCenters = ( SDL_Rect * ) malloc ( sizeof ( SDL_Rect ) ) ;

	unsigned int i, j ; /* Used for a loop */
	int nb_bubx ;

	for ( i = 0 ; i < BUB_NY ; i++ )
	{
		/* The number of bubbles depends on lines 
		 * Indeed we can place 8 bubbles on the even lines while we can place only 7 bubbles for the odd lines */
		nb_bubx = ( i % 2 == 0 ) ? BUB_NX : BUB_NX - 1 ;

		/* Allocation of the "second dimension" of the array corresponding to rows */
		game->bub_center[i] = ( int * * ) malloc ( BUB_NX * sizeof ( int * ) ) ;

		for ( j = 0 ; j < nb_bubx ; j++ )
		{
			/* Allocation of the "final dimension" of the array corresonding to the center of bubbles */
			game->bub_center[i][j] = ( int * ) malloc ( 2 * sizeof ( int ) ) ;

			/* We are going to calculate the coordinates of the various possible positions */
			tempCenters = calculPosBub ( i, j, tempCenters ) ; /* A VOIR */

			/* We add BUB_SIZE/2 to the coordinates to obtain the center */
			game->bub_center[i][j][0] = tempCenters->x + BUB_SIZE / 2 ;
			game->bub_center[i][j][1] = tempCenters->y + BUB_SIZE / 2 ;
		}
	}

	free ( tempCenters ) ;

}

/* Free the space assigned for the array indicating the presence or not of a bubble */
void bubarray_free ( game_t * game )
{
	unsigned int i ;

	for ( i = 0 ; i < BUB_NY ; i++ )
	{

		free ( game->bub_array[i] ) ;

	}

	free ( game->bub_array ) ;
}

/* We free the space assigned for the picture storing the centers of bubbles. */
void bubarray_freecenters ( game_t * game )
{
	unsigned i, j ; /* Used for a loop */
	int nb_bubx ;

	for ( i = 0 ; i < BUB_NY ; i++ )
	{
		/* The number of bubbles depends on lines 
		 * Indeed we can place 8 bubbles on the even lines while we can place only 7 bubbles for the odd lines */
		nb_bubx = ( i % 2 == 0 ) ? BUB_NX : BUB_NX - 1 ;

		for ( j = 0 ; j < nb_bubx ; j++ )
		{
			free ( game->bub_center[i][j] ) ;
		}

		free ( game->bub_center[i] ) ;
	}

	free ( game->bub_center ) ;
}

/* Calculate the different possible positions of bubbles on the game board */
SDL_Rect * calculPosBub ( unsigned int i, unsigned int j, SDL_Rect * bubPos )
{
	/* Distance between two bubbles ( varies according to the parity of 'line' ) */
	unsigned int dx ;
	dx = ( BOARD_RIGHT - BOARD_LEFT ) / BUB_NX ; /* = ( BOARD_RIGHT - BOARD_LEFT - BUB_SIZE ) / 7 for odd lines */

	/* The position depends on the parity of the line. If we are on an even line, then there are 8 bubbles */
	/* Otherwise, we add a half-bubble to the left board */
	bubPos->x = ( i % 2 == 0 ) ? BOARD_LEFT + j*dx : BOARD_LEFT + BUB_SIZE / 2 + j*dx ;
	bubPos->y = BOARD_TOP + 35 * i ; /* 35 =  ( 40 * sqrt(3) ) / 2 */

	return bubPos ;
}

void bubPosInit ( bubble_t * bubble, game_t * game )
{
	bubble->color = 2 ; /* Faire fonction rand */
	bubble->sprite = game->bub_colors[bubble->color] ;
	bubble->launched = 0 ;
	bubble->isMoving = 0 ;
	bubble->launcher_x = BUB_STARTX ;
	bubble->launcher_y = BUB_STARTY ;

	bubble->pos.x = bubble->launcher_x ;
	bubble->pos.y = bubble->launcher_y ;

	bubble->x = bubble->launcher_x ;
	bubble->y = bubble->launcher_y ;
} 
#endif