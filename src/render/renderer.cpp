#include "renderer.hpp"

Renderer::Renderer() :
    window(nullptr), renderer(nullptr), canvas(nullptr)
{
    window = SDL_CreateWindow(
        "tetris",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        0
    );

    if (window == nullptr) 
        std::cout << "Failed to create window!" << '\n';

    renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED
    );

    if (renderer == nullptr) 
        std::cout << "Failed to create renderer!" << '\n'; 

    canvas = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_TARGET,
        SCREEN_WIDTH,
        SCREEN_HEIGHT
    );

    if (canvas == nullptr)
        std::cout << "Failed to create canvas!" << '\n';
}

SDL_Renderer *Renderer::get_renderer() {
    return renderer;
}

SDL_Texture *Renderer::get_canvas() {
    return canvas;
}

Renderer::~Renderer() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_DestroyTexture(canvas);
    renderer = nullptr;
    window = nullptr;
    canvas = nullptr;
    SDL_Quit();
}
