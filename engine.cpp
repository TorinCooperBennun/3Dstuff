/* Standard libraries */
#include <fstream>
#include <iostream>
#include <string>

/* OpenGL and related */
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

/* SDL */
#include <SDL2/SDL.h>

/* Local headers */
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
    SDL_GL_DeleteContext(gl_context);
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
    /* Deal with parameters (default if < 1) */
    width      = (w > 0)   ? w   : width;
    height     = (h > 0)   ? h   : height;
    frames_sec = (fps > 0) ? fps : frames_sec;
    ticks_sec  = (tps > 0) ? tps : ticks_sec;

    std::cout << "Resolution:        " << width << " x " << height << std::endl
              << "Frames per second: " << frames_sec << std::endl
              << "Ticks per second:  " << ticks_sec << std::endl;

    /* Set OpenGL attributes for later context creation*/
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    /* Create window */
    window = SDL_CreateWindow("bullshit", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
    if (window == NULL) {
        sdl_fatal_error();
    }

    /* Create renderer */
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_TARGETTEXTURE);
    if (renderer == NULL) {
        sdl_fatal_error();
    }

    /* Create OpenGL context */
    gl_context = SDL_GL_CreateContext(window);
    if (gl_context == NULL) {
        sdl_fatal_error();
    }

    /* Init GLEW (experimental mode for OpenGL 3.3 */
    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        fatal_error("Failed to initialise GLEW!");
    }

    /* Set clear colour, load shaders from file */
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    shader_program = load_shaders("vertexshader", "fragmentshader");

    inited = true;
    return NOT_FUCKED;
}


/* loop()
 * Main loop.
 */
int engine_config::loop()
{
    /********** Generating matrices with OpenGL Mathematics (glm) **********/

    /* 45 degree FoV, 4:3 aspect ratio, 0.1 - 100 unit*/
    glm::mat4 proj_mat = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);

    /* Camera at (4,3,3) in world space, pointing at (0, 0, 0), the right way up (represented by (0, 1, 0)) */
    glm::mat4 view_mat = glm::lookAt(glm::vec3(4, 3, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

    /* Identity matrix of model */
    glm::mat4 model_mat = glm::mat4(1.0f);

    /* Combine them to get the mvp matrix */
    glm::mat4 mvp_mat = proj_mat * view_mat * model_mat;

    /********** Creating vertices **********/

    /* Create a vertex array */
    GLuint varray;
    glGenVertexArrays(1, &varray);
    glBindVertexArray(varray);

    /* Triangle (3 vertices) */
    static const GLfloat data[] = {
        -1.0f, -1.0f, 0.0f,
         1.0f, -1.0f, 0.0f,
         0.0f,  1.0f, 0.0f,
    };

    /* Put data into vertex buffer */
    GLuint vbuffer;
    glGenBuffers(1, &vbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);

    /* Get ID of matrix 'mvp' (name used in vertex shader) */
    GLuint matrix_id = glGetUniformLocation(shader_program, "mvp");

    std::cout << "Beginning main loop." << std::endl;

    /* Main loop */
    bool closed = false;
    SDL_Event event;
    while (!closed) {

        /* SDL events */
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    std::cout << "Application closed." << std::endl;
                    closed = true;
                    break;
                default:
                    break;
            }
        }
        
        /* Clear screen */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        /* Specify shader program */
        glUseProgram(shader_program);

        /* Send the mvp matrix to the vertex shader using ID retrieved earlier */
        glUniformMatrix4fv(matrix_id, 1, GL_FALSE, &mvp_mat[0][0]);

        /* Set the vertex buffer as the vertex array's source */
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vbuffer);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

        /* Draw vertex buffer as triangle */
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDisableVertexAttribArray(0);

        /* Swap buffers through SDL */
        SDL_GL_SwapWindow(window);

    }

    return NOT_FUCKED;
}


/* load_shaders(const char *vertex_shader, const char *fragment_shader)
 * Load and compile shaders. Returns shader program ID.
 */
GLuint engine_config::load_shaders(const char *vertex_shader, const char *fragment_shader)
{
    GLuint v_shader = glCreateShader(GL_VERTEX_SHADER);
    GLuint f_shader = glCreateShader(GL_FRAGMENT_SHADER);
    GLuint program_id;

    std::string shader;

    shader = read_file_contents(vertex_shader);
    if (shader.empty()) {
        fatal_error("Failed to read vertex shader file.");
    }

    std::cout << "Compiling vertex shader: " << vertex_shader << std::endl;
    const char *vertex_code = shader.c_str();
    glShaderSource(v_shader, 1, (const GLchar **)&vertex_code, NULL);
    glCompileShader(v_shader);

    shader = read_file_contents(fragment_shader);
    if (shader.empty()) {
        fatal_error("Failed to read fragment shader file.");
    }

    std::cout << "Compiling fragment shader: " << fragment_shader << std::endl;
    const char *fragment_code = shader.c_str();
    glShaderSource(f_shader, 1, (const GLchar **)&fragment_code, NULL);
    glCompileShader(f_shader);

    std::cout << "Linking shader program." << std::endl;
    program_id = glCreateProgram();
    glAttachShader(program_id, v_shader);
    glAttachShader(program_id, f_shader);
    glLinkProgram(program_id);

    glDeleteShader(v_shader);
    glDeleteShader(f_shader);

    return program_id;
}
