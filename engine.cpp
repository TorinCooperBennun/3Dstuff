#include <SDL2/SDL.h>
#include "engine.h"
#include "errors.h"
#include "utils.h"


/* constructor */
engine_config::engine_config()
{
    inited = false;
    window = NULL;
    renderer = NULL;
}


/* destructor */
engine_config::~engine_config()
{
    quit_all();
}


/* init(int w, int h)
 * Initialises subsystems and shit.
 */
int engine_config::init(int w, int h)
{
    window = SDL_CreateWindow("bullshit", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, 0);
    if (window == NULL) {
        sdl_fatal_error();
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_TARGETTEXTURE);
    if (renderer == NULL) {
        sdl_fatal_error();
    }

    return NOT_FUCKED;
}
