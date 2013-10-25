#ifndef ENGINE_H
#define ENGINE_H

#include <SDL2/SDL.h>
#include "errors.h"


class engine_config
{
    public:
        engine_config();
        ~engine_config();

        int init(int w, int h);

    private:
        bool inited;
        SDL_Window *window;
        SDL_Renderer *renderer;
};


enum engine_errors
{
    NOT_FUCKED = 0,
    FUCKED,
};


#endif
