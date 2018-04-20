#ifndef __BUBINIT_C__
#define __BUBINIT_C__

#include "../headers/struct.h"
#include "../headers/init.h"
#include "../headers/bubble.h"
#include "../headers/const.h"
#include "SDL.h"

/* Fills the different cells of the array with zeros */
void bubarray_init ( game_t * game )
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
	bubble->color = rand_color() ;
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

unsigned int rand_color ( void )
{

	unsigned int rand_number ;

	srand(time(NULL)) ; /* initialization of rand */
	rand_number = rand() % ( NUM_COLORS - 1 ) ; /* NOTE : current_col doit être compris entre 1 et 8, faire modif plus tard */
	
	return rand_number ;

}

bool bubismoving ( bubble_t * bub, game_t * game )
{

	/* First we calculate the projection of the bubble */
	double * proj_pos_x = ( double * ) malloc ( sizeof ( double ) ) ;
	double * proj_pos_y = ( double * ) malloc ( sizeof ( double ) ) ;

	* proj_pos_x = bub->x + bub->dx ;
	* proj_pos_y = bub->y + bub->dy ;

	/* Then we have to check : */
	/* If there is a collision whith an other bubble */
	if ( bub_isColliding ( bub, game, proj_pos_x, proj_pos_y ) )
	{
		bub->isMoving = false ;
		return false ;
	}

	/* If the bubble hits the top */
	if ( * proj_pos_y <= ( double ) BOARD_TOP )
	{
		* proj_pos_y = BOARD_TOP ;
		bub->isMoving = false ;

		return false ;
	}

	/* Rebounds on the right board */
	if ( * proj_pos_x >= ( double )( BOARD_RIGHT - BUB_SIZE ) )
	{

		/* Let's recalculate proj_pos_x */
		* proj_pos_x = * proj_pos_x + ( double )( 2 * BOARD_RIGHT ) + ( double )( 2 * BUB_SIZE ) ; /* A verifier */

		/* We have to change the direction of the bubble */
		bub->dx *= -1 ; 

	}

	/* Rebouns on the left board */
	else if ( * proj_pos_x <= ( double )( BOARD_LEFT ) )
	{

		/* Let's recalculate proj_pos_x */
		* proj_pos_x = ( double )( 2 * BOARD_LEFT ) - * proj_pos_x ;

		/* We have to change the direction of the bubble */
		bub->dx *= -1 ;

	}

	/* If we are here, the bubble is just moving without any collisions */
	else
	{
		bub->x = * proj_pos_x ;
		bub->y = * proj_pos_y ;

		bub->pos.x = ( int ) bub->x ;
		bub->pos.y = ( int ) bub->y ;
	}

	free ( proj_pos_x ) ;
	free ( proj_pos_y ) ;

	return true ;
}

bool bub_isColliding ( bubble_t * bub, game_t * game, double * proj_pos_x, double * proj_pos_y )
{
	/* The reference for positioning is the center of the bubbles, so we have to add BUB_SIZE / 2 to each coordinate */
	double x_currBub = * proj_pos_x + ( double )( BUB_SIZE / 2 ) ;
	double y_currBub = * proj_pos_y + ( double )( BUB_SIZE / 2 ) ;

	/* Variables used for a loop */
	unsigned int i, j, j_max ;

	for ( i = 0 ; i < BUB_NY ; i++ )
	{
		j_max = ( i % 2 == 0 ) ? BUB_NX : BUB_NX - 1 ;

		for ( j = 0 ; j < j_max ; j++ )
		{
			/* We check if there is a bubble at this position */
			if ( game->bub_array[i][j] > 0 )
			{
				double x_otherBub = game->bub_center[i][j][0] ;
				double y_otherBub = game->bub_center[i][j][1] ;

				/* We check if there is a collision between these two bubbles */
				double dist_between_centers = bub_getDistance ( x_currBub, y_currBub, x_otherBub, y_otherBub ) ;

				double collision_dist = BUB_SIZE * 0.87 ; /* 0.87 ~= ( sqrt(3) / 2 ) */

				if ( dist_between_centers < collision_dist )
				{
					return true ;
				}
			}
		}
	}

	return false ;
}

bool bub_is_below ( bubble_t * bub )
{
	return ( bub->pos.y > SCREEN_HEIGHT - LAUNCHER_HEIGHT ) ;
}

double bub_getDistance ( double bub1_x, double bub1_y, double bub2_x, double bub2_y )
{
	double dx = bub1_x - bub2_x ;
	double dy = bub1_y - bub2_y ;

	return sqrt ( abs( dx + dy ) ) ;
}

void bub_place ( bubble_t * bub, game_t * game )
{
	/* The reference for positioning is the center of the bubbles, so we have to add BUB_SIZE / 2 to each coordinate */
	double x_currBub = bub->x + ( double )( BUB_SIZE / 2 ) ;
	double y_currBub = bub->y + ( double )( BUB_SIZE / 2 ) ;

	/* Variables used for a loop */
	unsigned int i, j, j_max ;

	for ( i = 0 ; i < BUB_NY ; i++ )
	{
		j_max = ( i % 2 == 0 ) ? BUB_NX : BUB_NX - 1 ;

		for ( j = 0 ; j < j_max ; j++ )
		{
			/* We check if there is a bubble at this position */
			/* If there is no bubbles : */
			if ( game->bub_array[i][j] == 0 )
			{
				double x_otherBub = game->bub_center[i][j][0] ;
				double y_otherBub = game->bub_center[i][j][1] ;

				/* We check if there is a collision between these two bubbles */
				double dist_between_centers = bub_getDistance ( x_currBub, y_currBub, x_otherBub, y_otherBub ) ;

				if ( dist_between_centers <= BUB_SIZE / 2 )
				{
					game->bub_array[i][j] = bub->color ;
				}
			}
		}
	}
}

void bubLaunched ( bubble_t * bub, game_t * game )
{
	/* We check if the bubble is not moving */
	if ( !bub->isMoving )
	{
		/* So first, the bubble is on the launcher */
		/* We are going to calculate dx and dy according to the angle */

		/* Theta angle is the angle from horizontal *
		 * Start position : PI/2                    *
		 * We have 48 launcher images               *
		 * The sprite is firstly placed on the 22th *
		 * So we add 2 to have PI/2                 */

		double theta = ( PI * ( game->currentOrientation + 2 ) ) / LAUNCHER_DIV ;

		/* If we represent ourselves the trigonometric circle, we can see that it is inverted *
		 * (the zero is positioned in reality quite to the left and not to the right).        *
		 * So, if ( game->currentOrientation > 22 ) then we have a negative dx                *
		 * and if ( game->currentOrientation <= 22 )then we have a positive dx.               *
		 * We have to multiply dx by to solve this problem.                                   */

		bub->dx = -1 * cos ( theta ) * VELOCITY ;
		bub->dy = sin ( theta ) * VELOCITY ;

		/* Now we change the current state of the bubble : the bubble is moving */
		bub->isMoving = true ;
	}

	/* Now the launching is finished */
	bub->launched = false ;
}


#endif