#include "tetris.hpp"

void run(Renderer *renderer) {
    SDL_Renderer *rnd = renderer->get_renderer();
    SDL_Texture *canvas = renderer->get_canvas();
    
    Board board;
    Tetro tetro('i');

    SDL_Event event;
    bool running = true;

    while (running) {

        while(SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        Uint32 frame_start = SDL_GetTicks();

        SDL_SetRenderTarget(rnd, canvas);
        SDL_SetRenderDrawColor(rnd, 0, 0, 0, 255); 
        SDL_RenderClear(rnd);

        board.draw_board(rnd);
        tetro.draw_tetro(rnd, board.get_board());
        tetro.move_down();

        SDL_SetRenderTarget(rnd, NULL);
        SDL_SetRenderDrawColor(rnd, 0, 0, 0, 255);
        SDL_RenderClear(rnd);

        SDL_RenderCopy(rnd, canvas, NULL, NULL);
        SDL_RenderPresent(rnd);

        Uint32 frame_time = SDL_GetTicks() - frame_start;
        if (frame_time < FRAME_TIME)
            SDL_Delay(FRAME_TIME - frame_time);
    }
}
