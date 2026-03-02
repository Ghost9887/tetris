#include "tetris.hpp"

void run(Renderer *renderer) {
    SDL_Renderer *rnd = renderer->get_renderer();
    SDL_Texture *canvas = renderer->get_canvas();
    
    Board board;

    SDL_Event event;
    bool running = true;

    while (running) {
        SDL_SetRenderTarget(rnd, canvas);

        board.draw_board(rnd);

        while(SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        SDL_SetRenderTarget(rnd, NULL);
        SDL_RenderClear(rnd);
        SDL_RenderCopy(rnd, canvas, NULL, NULL);
        SDL_RenderPresent(rnd);
    }
}
