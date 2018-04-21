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

	frameImageInit ( screen ) ;
	launcherImageInit ( screen ) ;

	/* ************************* INITIALIZATION OF THE GAME ************************* */
     
	/* Declaration of the variables */
	game_t * game ;
	game = ( game_t * ) malloc ( sizeof ( game_t ) ) ;
  
	gameInit ( game ) ; /* Including bubarray_init */
	bubImageInit ( game ) ;

	/* ************************* INITIALIZATION OF THE SPRITES ********************** */

	/* We load sprites in the game */
	//loadingSprite ( game, screen ) ;

	/* We add the transparency so that the image are displayed without purple outline */
	setTransparency ( game, screen ) ;

	/* ************************* INITIALIZATION OF THE POSITIONS ******************** */

	/* Declaration of the variables */
	bubble_t * bub ;
	SDL_Rect * launcherPos ;

	bub = ( bubble_t * ) malloc ( sizeof ( bubble_t ) ) ;
	launcherPos = ( SDL_Rect * ) malloc ( sizeof ( SDL_Rect ) ) ;

	launcherPosInit ( launcherPos ) ;
	bubPosInit ( bub, game ) ;

	/* *********************** INITIALIZATION OF INPUT VARIABLE ******************** */

	input_t * in ;

	in = ( input_t * ) malloc ( sizeof ( input_t ) ) ;

	memset ( in, 0, sizeof ( * in ) ) ; /* Fill the whole array of zeros */

	/* *********************** INITIALIZATION OF TIME VARIABLE ********************* */

	/* Will regulate the number of image and the speed of the launcher */
	timecontrol_t * time ;

	time = ( timecontrol_t * ) malloc ( sizeof ( timecontrol_t ) ) ; 

	init_timer ( time ) ;

	/* ************************ BEGINNING OF THE GAME ****************************** */

	while ( !escape ( in ) )
	{
		 
		/* We refresh the screen to draw all the images/sprites */  
		updateScreen ( bub, launcherPos, screen, game, time ) ;

		/* We launch the timer */
		get_timer ( time ) ;

		/* We wait the "instructions" given by the user */
		HandleEvent ( in, bub ) ;
      
		/* We regulate the speed of the launcher thanks to a timer (50FPS) */
		if ( timereached ( time ) )
		{ 
		  launchermov ( in, game, bub, time ) ;
		}

		if ( bub->launched ) 
		{
		  bubLaunched ( bub, game ) ; 
		}
  
		if ( bub->isMoving )
		{  

		  /* We have to check different cases *  
		   * 1: The bubble is not moving anymore : maybe it hits the top board, or another bubble *
		   * 2: The bubble is below the limit of the game board : reinitialization of the game *
		   * 3: The bubble is moving : we calculate the trajectory and make it move normally */

		  if ( !bubismoving ( bub, game ) ) /* Include the 3rd case */
		  {
		    if ( bub_is_below ( bub ) ) /* 2nd case */
		    { 
		      bubarray_free ( game ) ; 
		      gameInit ( game ) ; 
		      bubPosInit ( bub, game ) ; 
		    } 
		    else 
		    {
		    	/* 1st case */
		      	/* We place the bubble in the array so that it will be displayed */
		    	bub_place ( bub, game ) ;

		    	/* Then we place the new bubble on the launcher */
		    	bubPosInit ( bub, game ) ;
		    }
		  }
		}

		SDL_UpdateRect ( screen->screen, 0, 0, 0, 0 ) ;

	}

	bubarray_freecenters ( game ) ;
	bubarray_init ( game ) ;
	free ( bub ) ;
	free ( game ) ;
	free ( launcherPos ) ;
	free ( in ) ;
	free ( time ) ;
	SDL_FreeSurface ( screen->launcher ) ;
	SDL_FreeSurface ( screen->frame ) ;
	SDL_FreeSurface ( screen->screen ) ;
	free ( screen ) ;
}