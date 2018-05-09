#ifndef __CONS_H__
#define __CONS_H__
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <stdbool.h>
#include "SDL.h"
#include <time.h>
#include <SDL/SDL_ttf.h>

/* Approximate pi value */
#define PI 3.14159265359

/* Size of the window */
#define SCREEN_WIDTH  720
#define SCREEN_HEIGHT 540
#define BOARD_LEFT 200
#define BOARD_RIGHT 520
#define BOARD_TOP 31
#define BOARD_BOTTOM 422

/* In the launcher sprite, we have 45 images of a 187x157 picture, */
/* Size of one launcher image: */
#define LAUNCHER_WIDTH 187
#define LAUNCHER_HEIGHT 157
#define LAUNCHER_CENTER 94
#define LAUNCHER_DIV 48

/* Size and position of one bubble image */
#define BUB_SIZE 40
#define BUB_STARTX 339 // SCREEN_WIDTH - BUB_SIZE / 2
#define BUB_STARTY 457

/* Velocity of bubbles */
#define VELOCITY 2

/* Size of bub_array[BUB_NY][BUB_NX] */
#define BUB_NX 8 // max. number of bubbles in horizontal direction
#define BUB_NY 11 // max. number of bubbles in vertical direction

/* Number of different colors for bubbles */
#define NUM_COLORS 8

#define TOP_START BOARD_TOP - 13
#define TOP_HEIGHT 9

#define CHAIN_WIDTH 23

#endif
