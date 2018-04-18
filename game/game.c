#include "../headers/init.h"
#include "../headers/struct.h"
#include "gameinit.c"
#include "bubinit.c"
#include "launcherinit.c"
#include "handleevent.c"

int main ( int argc, char * argv[] )
{

	/* ************************ INITIALIZATION OF THE SCREEN ************************ */

	/* Declaration of the variables */
	init_t * screen ;
	screen = ( init_t * ) malloc ( sizeof ( init_t ) ) ;

	screenInit ( screen ) ;

	/* ************************* INITIALIZATION OF THE GAME ************************* */

	/* Declaration of the variables */
	game_t * game ;
	game = ( game_t * ) malloc ( sizeof ( game_t ) ) ;

	gameInit ( game ) ;

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
	int * previousTime ;
	int * currentTime ;

	*previousTime = 0 ;

	/* ************************ BEGINNING OF THE GAME ****************************** */

	while ( !escape ( &in ) )
	{

		*currentTime = SDL_GetTicks () ;

		HandleEvent ( &in, bub ) ;
		updateScreen ( bub ) ;

		if ( timereached ( &previousTime, &currentTime ) )
		{
			launchermov ( &in ) ;
		}

		if ( bub->launched )
		{
			bubLaunched ( ... ) ;
		}

		if ( bub->isMoving )
		{

		}

	}

	free ( bub ) ;
	free ( game ) ;
	free ( screen ) ;
	SDL_FreeSurface ( screen->launcher ) ;
	SDL_FreeSurface ( screen->frame ) ;
}