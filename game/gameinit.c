#ifndef __GAMEINIT_C__
#define __GAMEINIT_C__

#include "../headers/init.h"
#include "../headers/struct.h"
#include "../headers/bubble.h"
#include "../headers/const.h"
#include "bubinit.c"

void screenInit ( init_t * window )
{

	SDL_Init ( SDL_INIT_VIDEO ) ;

	/* Set the title bar */
	SDL_WM_SetCaption ( "Puzzle Bobble Game", "Puzzle Bobble Game" ) ;

	/* Create windows */
	window->screen = SDL_SetVideoMode ( SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0 ) ;

}

void frameImageInit ( init_t * window )
{
	SDL_Surface * temp ;

	/* Loading the frame */
	temp = SDL_LoadBMP ( "../img/gamebackground/frame_1p.bmp" ) ;
	window->frame = SDL_DisplayFormat ( temp ) ;

	SDL_FreeSurface ( temp ) ;
}

void launcherImageInit ( init_t * window )
{
	SDL_Surface * temp ;

	/* Loading the images for the launcher */
	temp = SDL_LoadBMP ( "../img/launcher/frame_launcher.bmp") ;
	window->launcher = SDL_DisplayFormat ( temp ) ;

	SDL_FreeSurface ( temp ) ;
}

void bubImageInit ( game_t * game )
{

	SDL_Surface * temp ;

	/* Loading the images for the bubble */
	temp = SDL_LoadBMP ( "../img/bubs/bub_black.bmp" ) ;
	game->bub_colors[0] = SDL_DisplayFormat ( temp ) ;

	temp = SDL_LoadBMP ( "../img/bubs/bub_blue.bmp" ) ;
	game->bub_colors[1] = SDL_DisplayFormat ( temp ) ;

	temp = SDL_LoadBMP ( "../img/bubs/bub_green.bmp" ) ;
	game->bub_colors[2] = SDL_DisplayFormat ( temp ) ;

	temp = SDL_LoadBMP ( "../img/bubs/bub_orange.bmp" ) ;
	game->bub_colors[3] = SDL_DisplayFormat ( temp ) ;

	temp = SDL_LoadBMP ( "../img/bubs/bub_purple.bmp" ) ;
	game->bub_colors[4] = SDL_DisplayFormat ( temp ) ;

	temp = SDL_LoadBMP ( "../img/bubs/bub_red.bmp" ) ;
	game->bub_colors[5] = SDL_DisplayFormat ( temp ) ;

	temp = SDL_LoadBMP ( "../img/bubs/bub_white.bmp" ) ;
	game->bub_colors[6] = SDL_DisplayFormat ( temp ) ;

	temp = SDL_LoadBMP ( "../img/bubs/bub_yellow.bmp" ) ;
	game->bub_colors[7] = SDL_DisplayFormat ( temp ) ;
	
	SDL_FreeSurface ( temp ) ;
	
	game->currentOrientation = 22 ;
}

void gameInit ( game_t * game, ceiling_t * ceil )
{

	/* Initialize bub array which informs about the positions and the colors of bubbles displayed on the game board */
	game->bub_array = ( int * * ) malloc ( BUB_NY * sizeof ( int * ) ) ;

	/* We have to make sure that there are no bubbles on the screen at first */
	bubarray_init ( game ) ;

	/* We fill the cells of the array with the different possible coordinates of the bubbles */
	game->bub_center = ( int * * * ) malloc ( BUB_NY * sizeof ( int * * ) ) ;
	bubarray_initcenters ( game, ceil ) ;

	/* We first fill the cells of this array with zeros */
	game->bub_connected_component = ( int * * ) malloc ( BUB_NY * sizeof ( int * ) ) ;
	bubcomponent_init ( game ) ;

	/* We have to init the file */
	game->bub_fifo = ( int * * ) malloc ( BUB_NY * BUB_NX * sizeof ( int * ) ) ;
	bubfile_init ( game ) ;

}

void ceilingInit ( ceiling_t * ceil )
{

	SDL_Surface * temp ;

	/* Loading the image of the ceiling */
	temp = SDL_LoadBMP ( "../img/top/frame_top.bmp" ) ;
	ceil->image_ceiling = SDL_DisplayFormat ( temp ) ;

	/* Loading the image of the chain */
	temp = SDL_LoadBMP ( "../img/top/frame_chain.bmp") ;
	ceil->image_chain = SDL_DisplayFormat ( temp ) ;

	SDL_FreeSurface ( temp ) ;

	ceil->position.x = BOARD_LEFT ;
	ceil->position.y = BOARD_TOP ; /* It's not important at this state */

	ceilingstateInit ( ceil ) ;

}

void ceilingstateInit ( ceiling_t * ceil )
{
	ceil->state = 0 ;
}

void freeScreen ( init_t * window )
{
	free ( window ) ;
}

void setTransparency ( game_t * game, init_t * window, ceiling_t * ceil ) 
{
	int colorkey ;
	unsigned int i ;

	colorkey = SDL_MapRGB ( window->screen->format, 255, 0, 255 ) ;

	/* Set frame transparency */
	SDL_SetColorKey ( window->frame, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey ) ;

	/* Set launcher transparency */
	SDL_SetColorKey ( window->launcher, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey ) ;

	/* Set bubbles transparency */
	for ( i = 0 ; i < NUM_COLORS ; i++ )
	{
		SDL_SetColorKey ( game->bub_colors[i], SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey ) ;
	}

	SDL_SetColorKey ( ceil->image_ceiling, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey ) ;
	SDL_SetColorKey ( ceil->image_chain, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey ) ;
}

void updateScreen ( bubble_t * bub, SDL_Rect * launcher , init_t * window, game_t * game, timecontrol_t * timer, ceiling_t * ceil )
{
	unsigned int i, j ;
	unsigned int j_max ;
	int color ; /* Will be the color of the cache (black) */
	SDL_Rect * temp ;
	
	temp = ( SDL_Rect * ) malloc ( sizeof ( SDL_Rect ) ) ;

	/* First, we draw a black cache */
	SDL_Rect cache ;
	cache.x = 0 ;
	cache.y = 0 ;
	cache.w = SCREEN_WIDTH ;
	cache.h = SCREEN_HEIGHT ;

	color = SDL_MapRGB ( window->screen->format, 0, 0, 0 ) ;

	SDL_FillRect ( window->screen, &cache, color ) ;

	/* Then, we draw the game board */
	SDL_Rect framePos ;
	framePos.x = 0 ;
	framePos.y = 0 ;

	SDL_BlitSurface ( window->frame, NULL, window->screen, &framePos ) ;

	/* We can draw the top falling */
	SDL_Rect ceiling ;
	SDL_Rect chain ;
	SDL_Rect test ;

	ceiling.x = ceil->position.x ;
	ceiling.y = TOP_START + ceil->state * 35 ;

	chain.x = 0 ;
	chain.y = 0 ;
	chain.h = TOP_START + ceil->state * 35 - 25 ;
	chain.w = CHAIN_WIDTH ;

	test.x = ( BOARD_RIGHT + BOARD_LEFT - chain.w ) / 2 ;
	test.y = ceil->position.y ; 

	if ( ceil->state > 0 )
	{
		SDL_BlitSurface ( ceil->image_chain, &chain, window->screen, &test ) ;
		SDL_BlitSurface ( ceil->image_ceiling, NULL, window->screen, &ceiling ) ;
	}


	/* Then, we draw the launcher */
	SDL_Rect launcherImg ;
	launcherImg.w = LAUNCHER_WIDTH ;
	launcherImg.h = LAUNCHER_HEIGHT ;
	launcherImg.x = 0 ;
	launcherImg.y = LAUNCHER_HEIGHT * game->currentOrientation ;

	SDL_BlitSurface ( window->launcher, &launcherImg, window->screen, launcher ) ;
	
	/* Finally, we draw the bubs */
	SDL_Rect bubRect ;
	
	bubRect.x = 0 ;
	bubRect.y = 0 ;
	bubRect.w = BUB_SIZE ;
	bubRect.h = BUB_SIZE ;
	
	for ( i = 0 ; i < BUB_NY ; i++ )
	{
	  j_max = ( i % 2 == 0 ) ? BUB_NX : BUB_NX - 1 ;
	  
	  for ( j = 0 ; j < j_max ; j++ )
	  {
	    /* We only draw the bubbles set to 1 in the array */
	    if ( game->bub_array[i][j] > 0 )
	    {
	      /* Get the position of bubbles */
	      temp = calculPosBub ( i, j, temp, ceil ) ;
	      
	      /* Display them */
	      SDL_BlitSurface ( game->bub_colors[game->bub_array[i][j] - 1], &bubRect, window->screen, temp ) ;
	    }
	  }
	}

	bubRect.y = bub->rotation * BUB_SIZE ;

	
	/* Display the current bubble which is moving */
	SDL_BlitSurface ( bub->sprite, &bubRect, window->screen, &(bub->pos) ) ; /* &(bub->position) ? */
	SDL_BlitSurface ( ceil->image_ceiling, NULL, window->screen, &ceiling ) ;

	free ( temp ) ;

	/* We update the time */
	get_timer ( timer ) ;
	
}

void update_timer ( timecontrol_t * timer )
{
	timer->previousTime = timer->currentTime ;
}

void init_timer ( timecontrol_t * timer )
{
	timer->previousTime = 0 ;
}

void get_timer ( timecontrol_t * timer )
{
	timer->currentTime = SDL_GetTicks() ;
}

void initBubblesOnBoard ( game_t * game, bubble_t * bubble )
{
	unsigned int i, j, j_max ;

	for ( i = 0 ; i < 3 ; i++ )
	{
		j_max = ( i % 2 == 0 ) ? BUB_NX : BUB_NX - 1 ;

		for ( j = 0 ; j < j_max ; j++ )
		{
			game->bub_array[i][j] = rand_color() ;
		}
	}

	bubble->rotation = 0 ;

}

void bubcomponent_init ( game_t * game )
{
	unsigned int i, j, j_max ;

	for ( i = 0 ; i < BUB_NY ; i++ )
	{

		game->bub_connected_component[i] = ( int * ) malloc ( BUB_NX * sizeof ( int ) ) ;

		j_max = ( i % 2 == 0 ) ? BUB_NX : BUB_NX - 1 ;

		for ( j = 0 ; j < j_max ; j++ )
		{
			game->bub_connected_component[i][j] = 0 ;
		}
	}


}


void bubfile_init ( game_t * game )
{
	unsigned int i ;

	for ( i = 0 ; i < BUB_NY * BUB_NX ; i++ )
	{
		game->bub_fifo[i] = ( int * ) malloc ( 2 * sizeof ( int ) ) ;
	}

	game->head = 0 ;
	game->tail = 0 ;
}

void freecomponent_array ( game_t * game )
{
	unsigned int i ;

	for ( i = 0 ; i < BUB_NY ; i++ )
	{

		free( game->bub_connected_component[i] ) ;
	}

}

bool we_have_a_winner ( game_t * game )
{
	unsigned int i, j, j_max ;

	for ( i = 0 ; i < BUB_NY ; i ++ )
	{
		j_max = ( i % 2 == 0 ) ? BUB_NX : BUB_NX - 1 ;

		for ( j = 0 ; j < j_max ; j++ )
		{
			if ( game->bub_array[i][j] > 0 )
			{
				return false ;
			}
		}
	}
	return true ;
}

bool sky_is_falling ( timecontrol_t * time, ceiling_t * ceil, game_t * game, bubble_t * bub ) 
{
	if ( time->currentTime - time->previousTime > 4000 )
	{
		ceil->state += 1 ;
		update_timer ( time ) ;
		bubarray_centersrecalcul ( game, ceil, bub ) ;
	} 

	if ( ceil->state == 11 )
	{
		return true ;
	}

	return false ;
}

int game_over ( bubble_t * bub, ceiling_t * ceil, game_t * game )
{
	printf("GAME OVER.\n") ; 
	ceilingstateInit ( ceil ) ;   
	bubarray_free ( game ) ; 
	gameInit ( game, ceil ) ; 
	bubPosInit ( bub, game ) ;   
	initBubblesOnBoard ( game, bub ) ;  
	bubcomponent_init ( game ) ;  
	return EXIT_SUCCESS ;
}
/* NOTE : FAIRE DES FREE POUR CES DEUX FONCTIONS POUR EVITER FUITE MEMOIRE */

#endif