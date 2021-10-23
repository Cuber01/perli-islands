#include <SDL.h>
#include <SDL_opengl.h>
#include <stdio.h>

#include "render.hpp"
#include "main.hpp"


void CRenderHandler::init()
{
   
    renderer = SDL_CreateRenderer(window, -1, 0); 

    if (renderer == NULL)
    {
        printf("Renderer failed to initialize. Error: %s\n", SDL_GetError());
        exit(1);
    }
    
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

    // main surface draw loop
    SDL_LockSurface(surface);

    unsigned char* pixels = (unsigned char*)surface -> pixels;
    int value;

    for (uint16_t x = 0; x < WINDOW_WIDTH; x++) {
        for (uint16_t y = 0; y < WINDOW_HEIGHT; y++) {

            //value = grid[x][y];

            if(value != 0)
            {
                //color_t color = value->getColor();

                // pixels[4 * (y * surface -> w + x) + 3] = 255;   //opacity

                // pixels[4 * (y * surface -> w + x) + 2] = color.r;   //red
                // pixels[4 * (y * surface -> w + x) + 1] = color.g;   //green
                // pixels[4 * (y * surface -> w + x) + 0] = color.b;   //blue   

            }

        }
    }

    SDL_UnlockSurface(surface);

    // create texture from surface
    texture = SDL_CreateTextureFromSurface(renderer, surface); 
    
    // copy texture over to renderer
    SDL_RenderCopy(renderer, texture, NULL, NULL); 

    SDL_RenderPresent(renderer);

    SDL_DestroyTexture(texture); //TODO keep one texture instead of destroying it every frame, see: SDL_Texture_Lock or SDL_Texture_Update
}

void CRenderHandler::clear()
{
    SDL_FillRect(surface, NULL, 0x000000);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}
    