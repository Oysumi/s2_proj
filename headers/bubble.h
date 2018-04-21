#ifndef __BUBBLE_H__
#define __BUBBLE_H__
#include "const.h"
#include "struct.h"

/* Fills the different cells of the array with zeros */
void bubarray_init ( game_t * game ) ;

void bubarray_initcenters ( game_t * game ) ;

void bubarray_free ( game_t * game ) ;

void bubarray_freecenters ( game_t * game ) ;

SDL_Rect * calculPosBub ( unsigned int i, unsigned int j, SDL_Rect * bubPos ) ;

void launchermov ( input_t * in, game_t * game, bubble_t * bubble, timecontrol_t * timer ) ;

void bubPosInit ( bubble_t * bubble, game_t * game ) ;

bool bubismoving ( bubble_t * bub, game_t * game ) ;

bool bub_isColliding ( bubble_t * bub, game_t * game, double * proj_pos_x, double * proj_pos_y ) ;

bool bub_is_below ( bubble_t * bub ) ;

double bub_getDistance ( double bub1_x, double bub1_y, double bub2_x, double bub2_y ) ;

int bub_place ( bubble_t * bub, game_t * game ) ;

void bubLaunched ( bubble_t * bub, game_t * game ) ;

#endif
