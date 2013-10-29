#ifndef ENGINE_H
#define ENGINE_H


/* OpenGL */
#include <GL/glew.h>

/* SDL */
#include <SDL2/SDL.h>


/* engine_config
 * Engine is basically run through this object
 */
class engine_config
{
    public:
        engine_config();
        ~engine_config();

        int init(int w, int h, int fps, int tps);
        int loop();

    private:
        bool inited;

        SDL_Window *window;
        SDL_Renderer *renderer;
        SDL_GLContext gl_context;

        int width;
        int height;
        int frames_sec;
        int ticks_sec;

        GLuint shader_program;

        GLuint load_shaders(const char *vertex_shader, const char *fragment_shader);
};


enum engine_errors
{
    NOT_FUCKED = 0,
    FUCKED,
};


#endif
