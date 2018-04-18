#include "../headers/struct.h"
#include "../headers/const.h"


bool timereached ( int previous, int current )
{
	if ( current - previous > 20 )
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
