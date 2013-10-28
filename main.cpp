#include <SDL2/SDL.h>
#include "engine.h"
#include "errors.h"
#include "utils.h"


engine_config cfg;


/* main(int argc, char *argv[])
 * Entry point
 */
int main(int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        sdl_fatal_error();
    }

    if (cfg.init(0, 0, 0, 0) != NOT_FUCKED) {
        fatal_error("Engine initialisation was FUCKED.");
    }

    quit_all();

    return 0;
}
