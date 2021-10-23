#ifndef __MAIN_HPP
#define __MAIN_HPP

#include <stdint.h>

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600

extern SDL_Window* window;

extern int grid[WINDOW_WIDTH][WINDOW_HEIGHT];
extern int next[WINDOW_WIDTH][WINDOW_HEIGHT];


#endif