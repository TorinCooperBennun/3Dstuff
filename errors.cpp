#include "errors.h"
#include "utils.h"


void fatal_error(const char *str)
{
    fprintf(stderr, "%s\n", str);
    quit_all();
    exit(1);
}


void sdl_fatal_error()
{
    fatal_error(SDL_GetError());
}
