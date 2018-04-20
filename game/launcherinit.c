#include "../headers/struct.h"
#include "../headers/const.h"


bool timereached ( timecontrol_t * timer )
{
	if ( timer->currentTime - timer->previousTime > 20 )
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

void launchermov ( input_t * in, game_t * game, bubble_t * bubble )
{
  
 if ( in->key[SDLK_LEFT] )
 {
   if ( !bubble->isMoving ) /* So we can't change the direction of the bubble during the movement */
   {
     if ( game->currentOrientation > 0 )
     {
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
       game->currentOrientation += 1 ;
     }
   }
 }
 
}