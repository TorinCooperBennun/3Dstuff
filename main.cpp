/* headers and shit */
#include "main.h"


engine_config cfg;


/* entry point */
int main(int argc, char **argv)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        sdl_fatal_error();
    }

    if (cfg.init(800, 600) != NOT_FUCKED) {
        fatal_error("Engine initialisation was FUCKED.");
    }

    return 0;
}
