#include <SDL2/SDL.h>
#include "errors.h"
#include "utils.h"


/* fatal_error(const char *str)
 * Prints string to stderr and quits with return code 1
 */
void fatal_error(const char *str)
{
    fprintf(stderr, "%s\n", str);
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
