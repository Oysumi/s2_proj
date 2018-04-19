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

void launchermov ( input_t * in, game_t * game, int * previousTime, int * currentTime, bubble_t * bubble ) ;

#endif