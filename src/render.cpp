#include <SDL.h>
#include <SDL_opengl.h>
#include <stdio.h>

#include "render.hpp"
#include "main.hpp"


void CRenderHandler::init()
{
   
    // renderer = SDL_CreateRenderer(window, -1, 0); 

    // if (renderer == NULL)
    // {
    //     printf("Renderer failed to initialize. Error: %s\n", SDL_GetError());
    //     exit(1);
    // }
    
    surface = SDL_CreateRGBSurface(SDL_SWSURFACE, WINDOW_WIDTH, WINDOW_HEIGHT, 32, 0, 0, 0, 0);

    if(surface == NULL) 
    {
        printf("Failed to create surface: %s\n", SDL_GetError());
        exit(1);
    }

    //SDL_RenderSetScale(renderer, SCALE, SCALE);

}


void CRenderHandler::draw()
{
    clear();

    surface = SDL_LoadBMP("test.bmp");
    

    if (!surface) {
        printf("Failed to load image. Error: %s", SDL_GetError());
        exit(1);
    }

    SDL_FreeSurface(surface);

}

void CRenderHandler::clear()
{
    SDL_FillRect(surface, NULL, 0x000000);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}
    