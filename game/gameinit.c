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

void gameInit ( game_t * game )
{

	/* Initialize bub array which informs about the positions and the colors of bubbles displayed on the game board */
	game->bub_array = ( int * * ) malloc ( BUB_NY * sizeof ( int * ) ) ;

	/* We have to make sure that there are no bubbles on the screen at first */
	bubarray_init ( game ) ;

	/* We fill the cells of the array with the different possible coordinates of the bubbles */
	game->bub_center = ( int * * * ) malloc ( BUB_NY * sizeof ( int * * ) ) ;
	bubarray_initcenters ( game ) ;

}

void loadingSprite ( game_t * game, init_t * window )
{
	frameImageInit ( window ) ;
	launcherImageInit ( window ) ;
	bubImageInit ( game ) ;
}

void freeScreen ( init_t * window )
{
	free ( window ) ;
}

void setTransparency ( game_t * game, init_t * window ) 
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
}

void updateScreen ( bubble_t * bub, SDL_Rect * launcher , init_t * window, game_t * game, timecontrol_t * timer )
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
	      temp = calculPosBub ( i, j, temp ) ;
	      
	      /* Display them */
	      SDL_BlitSurface ( game->bub_colors[game->bub_array[i][j] - 1], &bubRect, window->screen, temp ) ;
	    }
	  }
	}
	
	/* Display the current bubble which is moving */
	SDL_BlitSurface ( bub->sprite, &bubRect, window->screen, &(bub->pos) ) ; /* &(bub->position) ? */
	
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

#endif