#include "../headers/struct.h"
#include "../headers/const.h"


bool timereached ( timecontrol_t * timer )
{
	if ( timer->currentTime - timer->previousTime > 30 )
	{
		return true ;
	}

	return false ;
}

void launcherPosInit ( SDL_Rect * launcher )
{
	launcher->x = ( SCREEN_WIDTH - LAUNCHER_WIDTH ) / 2 ;
	launcher->y = SCREEN_HEIGHT - LAUNCHER_HEIGHT ;
}

void launchermov ( input_t * in, game_t * game, bubble_t * bubble, timecontrol_t * timer )
{
  
 if ( in->key[SDLK_LEFT] )
 {
   if ( !bubble->isMoving ) /* So we can't change the direction of the bubble during the movement */
   {
     if ( game->currentOrientation > 0 )
     {
     	if ( bubble->rotation < 22 )
     	{
     		bubble->rotation += 1 ;
     	}
     	else
     	{
     		bubble->rotation = 0 ;
     	}
       	game->currentOrientation -= 1 ;
     }
   }
 }
 
 if ( in->key[SDLK_RIGHT] )
 {
   if ( !bubble->isMoving ) /* So we can't change the direction of the bubble during the movement */
   {
     if ( game->currentOrientation < 44 )
     {
     	if ( bubble->rotation < 22 )
     	{
     		bubble->rotation += 1 ;
     	}
     	else
     	{
     		bubble->rotation = 0 ;
     	}
       	game->currentOrientation += 1 ;
     }
   }
 }

 update_timer ( timer ) ;
 
}