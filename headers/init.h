#ifndef __INIT_H__
#define __INIT_H__
#include "const.h"
#include "struct.h"

void screenInit ( init_t * window ) ;

void frameImageInit ( init_t * window ) ;

void launcherImageInit ( init_t * window ) ;

void bubImageInit ( game_t * game ) ;

void gameInit ( game_t * game ) ;

void ceilingInit ( ceiling_t * ceil ) ;

void loadingSprite ( game_t * game, init_t * window ) ;

void freeScreen ( init_t * window ) ;

void setTransparency ( game_t * game, init_t * window, ceiling_t * ceil )  ;

void updateScreen ( bubble_t * bub, SDL_Rect * launcher , init_t * window, game_t * game, timecontrol_t * timer, ceiling_t * ceil ) ;

void update_timer ( timecontrol_t * timer ) ;

void init_timer ( timecontrol_t * timer ) ;

void get_timer ( timecontrol_t * timer ) ;

unsigned int rand_color ( void ) ;

void bubcomponent_init ( game_t * game ) ;

void bubfile_init ( game_t * game ) ;

void freecomponent_array ( game_t * game ) ;

bool we_have_a_winner ( game_t * game ) ;

#endif
