#include <SDL.h>
#include <iostream>
#include <stdio.h>
#include <stdint.h>
#include <cstdlib>
#include <memory>
#include <time.h>

#include <libnoise/noise.h>

#include "main.hpp"
#include "render.hpp"


// sdl
SDL_Window* window = NULL;
SDL_Event event;

//int
uint16_t lastKeyboardKeyPressed;
uint8_t  lastMouseKeyPressed;
uint32_t lastId;

//bool
bool mouseIsPressed = false;
bool running = true;


// grid
int grid[WINDOW_WIDTH][WINDOW_HEIGHT];
int next[WINDOW_WIDTH][WINDOW_HEIGHT];

int cursor_x;
int cursor_y;

using namespace noise;

// objects
CRenderHandler RenderHandler;

void init()
{
    
    // initalize rand
    srand((unsigned)time(NULL));

    // initalize video
    if( SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf( "SDL failed to initialize. Error: %s\n", SDL_GetError() );
        exit(1);
    }

    // setup window
    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_SHOWN);

    // create window
	window = SDL_CreateWindow("Perli Islands by @Cuber01", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, window_flags);

	if(window == NULL)
	{
		printf( "Window could not be created. SDL_Error: %s\n", SDL_GetError() );
        exit(1);
	} 

    RenderHandler.init();

}

void quit()
{
    SDL_DestroyRenderer( RenderHandler.renderer );
	SDL_DestroyWindow( window );
	SDL_Quit();
}

void handleEvent(SDL_Event* event)
{


    switch (event->type)
    {
            
        case SDL_MOUSEMOTION:
            SDL_GetMouseState( &cursor_x, &cursor_y );
            break;

        case SDL_MOUSEBUTTONDOWN:
            lastMouseKeyPressed = event->button.button;
            mouseIsPressed = true;
            break;

        case SDL_MOUSEBUTTONUP:
            mouseIsPressed = false;
            break;

    }

    switch (event->type)
    {

    case SDL_KEYDOWN:
        lastKeyboardKeyPressed = event->key.keysym.sym;
        break;

    case SDL_QUIT:
        running = false;
        break;

    }

}

void reactToEvent()
{
    if(mouseIsPressed)
    {
        if(lastMouseKeyPressed == SDL_BUTTON_LEFT)
        {

        } else if (lastMouseKeyPressed == SDL_BUTTON_RIGHT) 
        {
            
        }   
         
    } else 
    {

        switch (lastKeyboardKeyPressed)
        {
            default:
                break;
        }

    }
}

void updateParticles()
{



}

void main_loop()
{
  
    reactToEvent();

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        handleEvent(&event);
    }


    memset( next, 0, sizeof(next) );

    updateParticles();

    RenderHandler.draw(); 

    memcpy( grid, next, sizeof(grid) );

}

int main(int argc, char *argv[])
{
    init();

    module::Perlin myModule;
    double value = myModule.GetValue (1.25, 0.75, 0.5);
    std::cout << value << std::endl;

    while(running)
    {
        main_loop();
    }

    quit();

	return 0;
}
