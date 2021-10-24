#include <SDL.h>
#include <iostream>
#include <stdio.h>
#include <stdint.h>
#include <cstdlib>
#include <memory>
#include <time.h>

#include <libnoise/noise.h>
#include "noiseutils.h"

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

// cursor pos
int cursor_x;
int cursor_y;

using namespace noise;

// objects
CRenderHandler RenderHandler;

module::RidgedMulti PerlinModule;
//module::RidgedMulti mountainTerrain;

utils::NoiseMap heightMap;
utils::NoiseMapBuilderPlane heightMapBuilder;

utils::RendererImage img_renderer;
utils::Image image;

void init()
{
    
    // initalize video
    if( SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf( "SDL failed to initialize. Error: %s\n", SDL_GetError() );
        exit(1);
    }

    // setup window
    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_SHOWN);

    // create window
	// window = SDL_CreateWindow("Perli Islands by @Cuber01", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, window_flags);

	// if(window == NULL)
	// {
	// 	printf( "Window could not be created. SDL_Error: %s\n", SDL_GetError() );
    //     exit(1);
	// } 

    // from 1-6, more than 6 yields almost no additional effect. changes the amount of detail
    PerlinModule.SetOctaveCount(6);

    // from 1-16. bigger = smaller islands
    PerlinModule.SetFrequency(1);

    // from 0-1. changes the amount of fuzziness
    //PerlinModule.SetPersistence(0.5);

    heightMapBuilder.SetSourceModule(PerlinModule);
    heightMapBuilder.SetDestNoiseMap(heightMap);

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


void main_loop()
{
  
    reactToEvent();

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        handleEvent(&event);
    }

}


int main(int argc, char *argv[])
{
    init();


    heightMapBuilder.SetDestSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    heightMapBuilder.SetBounds(0.0, 15.0, 0.0, 15.0);

    heightMapBuilder.Build();

    img_renderer.SetSourceNoiseMap(heightMap);
    img_renderer.SetDestImage(image);

    img_renderer.ClearGradient ();
    // img_renderer.AddGradientPoint (-1.0000, utils::Color (  0,   0, 128, 255)); // deeps
    // img_renderer.AddGradientPoint (-0.2500, utils::Color (  0,   0, 255, 255)); // shallow
    // img_renderer.AddGradientPoint ( 0.0000, utils::Color (  0, 128, 255, 255)); // shore
    // img_renderer.AddGradientPoint ( 0.0625, utils::Color (240, 240,  64, 255)); // sand
    // img_renderer.AddGradientPoint ( 0.1250, utils::Color ( 32, 160,   0, 255)); // grass
    // img_renderer.AddGradientPoint ( 0.3750, utils::Color (224, 224,   0, 255)); // dirt
    // img_renderer.AddGradientPoint ( 0.7500, utils::Color (128, 128, 128, 255)); // rock
    // img_renderer.AddGradientPoint ( 1.0000, utils::Color (255, 255, 255, 255)); // snow

    img_renderer.AddGradientPoint (-1.00, utils::Color ( 32, 160,   0, 255)); // grass
    img_renderer.AddGradientPoint (-0.25, utils::Color (224, 224,   0, 255)); // dirt
    img_renderer.AddGradientPoint ( 0.25, utils::Color (128, 128, 128, 255)); // rock
    img_renderer.AddGradientPoint ( 1.00, utils::Color (255, 255, 255, 255)); // snow

    img_renderer.EnableLight();
    img_renderer.SetLightBrightness(1.8);

    img_renderer.Render();

    utils::WriterBMP writer;
    writer.SetSourceImage(image);
    writer.SetDestFilename("test.bmp");
    writer.WriteDestFile();



    while(running)
    {
        main_loop();
    }

    quit();

	return 0;
}
