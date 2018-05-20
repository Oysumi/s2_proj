#ifndef __BUBBLE_H__
#define __BUBBLE_H__
#include "const.h"
#include "struct.h"

/* Fills the different cells of the array with zeros */
void bubarray_init ( game_t * game ) ;

void bubarray_initcenters ( game_t * game, ceiling_t * ceil ) ;

int bubarray_centersrecalcul ( game_t * game, ceiling_t * ceil, bubble_t * bub, timecontrol_t * time ) ;

void bubfalling_init ( game_t * game ) ;

void bubfalling_free_rect ( game_t * game ) ;

void bubarray_free ( game_t * game ) ;

void bubarray_freecenters ( game_t * game ) ;

SDL_Rect * calculPosBub ( unsigned int i, unsigned int j, SDL_Rect * bubPos, ceiling_t * ceil ) ;

void launchermov ( input_t * in, game_t * game, bubble_t * bubble, timecontrol_t * timer ) ;

void bubPosInit ( bubble_t * bubble, game_t * game ) ;

unsigned int give_a_bubble ( bubble_t * bubble, game_t * game ) ;

bool bubismoving ( bubble_t * bub, game_t * game, ceiling_t * ceil ) ;

bool bub_isColliding ( bubble_t * bub, game_t * game, double * proj_pos_x, double * proj_pos_y ) ;

bool bub_is_below ( bubble_t * bub ) ;

double bub_getDistance ( double bub1_x, double bub1_y, double bub2_x, double bub2_y ) ;

int bub_place ( bubble_t * bub, game_t * game ) ;

void bubLaunched ( bubble_t * bub, game_t * game ) ;

void initBubblesOnBoard ( game_t * game, bubble_t * bubble ) ;

int connex ( game_t * game, ceiling_t * ceil, bool color ) ;

int fill_the_file ( game_t * game, unsigned int lig, unsigned int row, bool color ) ;

int delete_bub ( game_t * game, bool color, ceiling_t * ceil ) ;

bool bub_is_on_launcher ( bubble_t * bub ) ;

void bub_explosion ( game_t * game, unsigned int i ) ;

void bub_falling ( game_t * game, unsigned int i ) ;

void bub_disappears ( game_t * game ) ;

bool bub_isOut ( game_t * game, unsigned int i ) ;

#endif
