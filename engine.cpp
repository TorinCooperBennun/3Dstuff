#include <iostream>
#include <SDL2/SDL.h>
#include "engine.h"
#include "errors.h"
#include "utils.h"


/* constructor
 * Sets default values upon object creation
 */
engine_config::engine_config()
{
    inited = false;
    window = NULL;
    renderer = NULL;
    width = 800;
    height = 600;
    frames_sec = 60;
    ticks_sec = 60;
}


/* destructor
 * Destroys stuff and deletes object
 */
engine_config::~engine_config()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    inited = false;
}


/* init(int w, int h, int fps, int tps)
 * Initialises subsystems and shit.
 * w, h are window width and height.
 * fps, tps are frames per second and ticks per second.
 * If any arguments are < 1, defaults are used.
 */
int engine_config::init(int w, int h, int fps, int tps)
{
    width      = (w > 0)   ? w   : width;
    height     = (h > 0)   ? h   : height;
    frames_sec = (fps > 0) ? fps : frames_sec;
    ticks_sec  = (tps > 0) ? tps : ticks_sec;

    std::cout << "Resolution:        " << width << " x " << height << std::endl
              << "Frames per second: " << frames_sec << std::endl
              << "Ticks per second:  " << ticks_sec << std::endl;

    window = SDL_CreateWindow("bullshit", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    if (window == NULL) {
        sdl_fatal_error();
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_TARGETTEXTURE);
    if (renderer == NULL) {
        sdl_fatal_error();
    }

    inited = true;

    return NOT_FUCKED;
}
