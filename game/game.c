#include "../headers/init.h"
#include "../headers/struct.h"
#include "gameinit.c"
#include "bubinit.c"
#include "launcherinit.c"
#include "handleevent.c"

int main ( int argc, char * argv[] )
{

	/* Nb : INITIALISER QUE DES POINTEURS POUR QUE LE CODE SOIT HOMOGENE */
	/* FAIRE STRUCTURE TIME POUR SE SIMPLIFIER LA VIE */
	
	/* ************************ INITIALIZATION OF THE SCREEN ************************ */

	/* Declaration of the variables */
	init_t * screen ;
	screen = ( init_t * ) malloc ( sizeof ( init_t ) ) ;

	screenInit ( screen ) ;

	/* ************************* INITIALIZATION OF THE GAME ************************* */

	/* Declaration of the variables */
	game_t * game ;
	game = ( game_t * ) malloc ( sizeof ( game_t ) ) ;

	gameInit ( game ) ; /* Including bubarray_init */

	/* ************************* INITIALIZATION OF THE SPRITES ********************** */

	/* We load sprites in the game */
	loadingSprite ( game, screen ) ;

	/* We add the transparency so that the image are displayed without purple outline */
	setTransparency ( game, screen ) ;

	/* ************************* INITIALIZATION OF THE POSITIONS ******************** */

	/* Declaration of the variables */
	bubble_t * bub ;
	SDL_Rect * launcherPos ;

	bub = ( bubble_t * ) malloc ( sizeof ( bubble_t ) ) ;

	launcherPosInit ( launcherPos ) ;
	bubPosInit ( bub, game ) ;

	/* *********************** INITIALIZATION OF INPUT VARIABLE ******************** */

	input_t in ;
	memset ( &in, 0, sizeof ( in ) ) ; /* Fill the whole array of zeros */

	/* *********************** INITIALIZATION OF TIME VARIABLE ********************* */

	/* Will regulate the number of image and the speed of the launcher */
	int previousTime ;
	int currentTime ;

	previousTime = 0 ;

	/* ************************ BEGINNING OF THE GAME ****************************** */

	while ( !escape ( &in ) )
	{

		currentTime = SDL_GetTicks () ;

		HandleEvent ( &in, bub ) ;
		updateScreen ( bub, launcherPos, screen, game ) ;

		/* We regulate the speed of the launcher thanks to a timer (50FPS) */
		if ( timereached ( previousTime, currentTime ) )
		{
		  launchermov ( &in, game, &previousTime, &currentTime, bub ) ;
		}

		if ( bub->launched )
		{
		  bubLaunched ( ... ) ;
		}

		if ( bub->isMoving )
		{
		  /* We have to check different cases *
		   * 1: The bubble is not moving anymore : maybe it hits the top or another bubble *
		   * 2: The bubble is below the limit of the game board : reinitialization of the game *
		   * 3: The bubble is moving : we calculate the trajectory */
		  
		  /* 1st case */
		  if ( !bubismoving ( ... ) )
		  {
		    if ( bub_is_below ( ... ) )
		    {
		      bubarray_free ( game ) ;
		      gameInit ( game ) ;
		    }
		    else
		    {
		      /* We place the bubble in the array so that it will be displayed */
		    }
		  }
		 }
	}

	bubarray_freecenters ( game ) ;
	bubarray_init ( game ) ;
	free ( bub ) ;
	free ( game ) ;
	free ( screen ) ;
	SDL_FreeSurface ( screen->launcher ) ;
	SDL_FreeSurface ( screen->frame ) ;
}