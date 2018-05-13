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

	frameImageInit ( screen ) ;   
	launcherImageInit ( screen ) ;      

	/* ************************* INITIALIZATION OF THE GAME ************************* */
     
	/* Declaration of the variables */
	game_t * game ;
	game = ( game_t * ) malloc ( sizeof ( game_t ) ) ;

	ceiling_t * ceil ;
	ceil = ( ceiling_t * ) malloc ( sizeof ( ceiling_t ) ) ;  
  
  	ceilingInit ( ceil ) ;
	gameInit ( game, ceil ) ; /* Including bubarray_init */
	bubImageInit ( game ) ;       
 
	/* ************************* INITIALIZATION OF THE SPRITES ********************** */
 
	/* We add the transparency so that the image are displayed without purple outline */
	setTransparency ( game, screen, ceil ) ; 

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
   
	/* *********************** INITIALIZATION OF TIME VARIABLES ********************* */
 
	/* Will regulate the number of image and the speed of the launcher */
	timecontrol_t * time ; 
  
	time = ( timecontrol_t * ) malloc ( sizeof ( timecontrol_t ) ) ; 
 
	init_timer ( time ) ;  

	/* Allow the ceiling to fall */
	timecontrol_t * ceil_fall ;

	ceil_fall = ( timecontrol_t * ) malloc ( sizeof ( timecontrol_t ) ) ;

	init_timer ( ceil_fall ) ;
 
	/* ************************ BEGINNING OF THE GAME ****************************** */

	initBubblesOnBoard ( game, bub ) ;        
  
	while ( !escape ( in ) )
	{
		 
		/* We refresh the screen to draw all the images/sprites */  
		updateScreen ( bub, launcherPos, screen, game, time, ceil ) ;
       
		/* We launch the timer */
		get_timer ( time ) ; 

		/* We wait the "instructions" given by the user */
		HandleEvent ( in, bub ) ;
      
      	/* We check if the player won */
      	if ( we_have_a_winner ( game ) )
      	{
      		printf("CONGRATULATIONS ! YOU WIN !\n") ;
      		ceilingstateInit ( ceil ) ;
      		bubarray_free ( game ) ;  
		    gameInit ( game, ceil ) ; 
		    bubPosInit ( bub, game ) ;   
		    initBubblesOnBoard ( game, bub ) ;   
		    bubcomponent_init ( game ) ;    
      	} 

		/* We regulate the speed of the launcher thanks to a timer */
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
 
		  /* We have to check differen t cases *  
		   * 1: The bubble is not moving anymore : maybe it hits the top board, or another bubble *
		   * 2: The bubble is below the limit of the game board : reinitialization of the game *
		   * 3: The bubble is moving : we calculate the trajectory and make it move normally */

		  if ( !bubismoving ( bub, game, ceil ) ) /* Include the 3rd case */
		  {
		    if ( bub_is_below ( bub ) ) /* 2nd case */
		    {
		    	bub_place ( bub, game ) ;
		    	if ( connex ( game, ceil, true ) == 0 )
		    	{ 
		        	game_over ( bub, ceil, game ) ; 
		        }
		        else
		        {
		        	connex ( game, ceil, false ) ;
		        	bubPosInit ( bub, game ) ;
		        }          
		    }                  
		    else 
		    {     
		    	/* 1st case */       	           	  
		      	/* We place the bubble in the array so that it will be displayed */
		      	bub_place ( bub, game ) ; 
		      	connex ( game, ceil, true ) ; /* 1st step : with colors */
				connex ( game, ceil, false ) ; /* 2nd step : without colors */                       

		    	/* Then we place the new bubble on the launcher */
		    	bubPosInit ( bub, game ) ;    	         
		    }       
		  }         
		}        

		SDL_UpdateRect ( screen->screen, 0, 0, 0, 0 ) ; 
		get_timer ( ceil_fall ) ;
		sky_is_falling ( ceil_fall, ceil, game, bub ) ;          

	}
 
	bubarray_freecenters ( game ) ; 
	bubarray_init ( game ) ; 
	free ( bub ) ;
	free ( ceil ) ;
	free ( game ) ;  
	free ( launcherPos ) ;
	free ( in ) ;
	free ( time ) ;
	SDL_FreeSurface ( screen->launcher ) ;
	SDL_FreeSurface ( screen->frame ) ;
	SDL_FreeSurface ( screen->screen ) ;
	free ( screen ) ;
	/* NOTE : S'ASSURER DE NE PAS AVOIR DE FUITES MEMOIRES AVEC LES FREE */
}