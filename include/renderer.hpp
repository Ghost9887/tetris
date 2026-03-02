#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "common.hpp"

class Renderer {
public:
    Renderer();
    ~Renderer();
    SDL_Renderer *get_renderer();
    SDL_Texture *get_canvas();
private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *canvas;
};

#endif
