/* Standard libraries */
#include <iostream>

/* SDL */
#include <SDL2/SDL.h>

/* Local headers */
#include "errors.h"
#include "utils.h"


/* fatal_error(const char *str)
 * Prints string to stderr and quits with return code 1
 */
void fatal_error(const char *str)
{
    std::cerr << str << std::endl;
    quit_all();
    exit(1);
}


/* sdl_fatal_error()
 * Shortcut for fatal_error after SDL-related errors
 */
void sdl_fatal_error()
{
    fatal_error(SDL_GetError());
}
