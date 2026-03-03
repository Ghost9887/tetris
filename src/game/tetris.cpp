#include "tetris.hpp"

void run(Renderer *renderer) {
    SDL_Renderer *rnd = renderer->get_renderer();
    SDL_Texture *canvas = renderer->get_canvas();
    
    Board board;
    Tetro tetro('i');

    SDL_Event event;
    bool running = true;
    bool moved_down;
    
    Uint32 lastFallTime = SDL_GetTicks(); 
    const Uint32 fallDelay = 500;
    
    Player player;
    std::vector<Tetro> tetros;
    tetros.push_back(Tetro::create_random_tetro());
    player.set_current_tetro(&tetros.back());

    while (running) {

        if (player.get_current_tetro()->is_fixed()) {
            tetros.push_back(Tetro::create_random_tetro());
            player.set_current_tetro(&tetros.back());
        }

        moved_down = false;
        Uint32 frame_start = SDL_GetTicks();

        while(SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                running = false;
            }else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_LEFT:
                        Tetro::move(*player.get_current_tetro(), Left);
                        break;
                    case SDLK_RIGHT:
                        Tetro::move(*player.get_current_tetro(), Right);
                        break;
                    case SDLK_DOWN:
                        if (!moved_down) {
                            Tetro::move(*player.get_current_tetro(), Down);
                            moved_down = true;
                        }
                        break;
                    default: break;
                }
            }
        }

        SDL_SetRenderTarget(rnd, canvas);
        SDL_SetRenderDrawColor(rnd, 0, 0, 0, 255); 
        SDL_RenderClear(rnd);

        board.draw_board(rnd);
        Tetro::draw_tetros(tetros, rnd, board.get_board());

        Uint32 now = SDL_GetTicks();
        if (now - lastFallTime >= fallDelay && !moved_down) {
            Tetro::move(*player.get_current_tetro(), Down);
            lastFallTime = now;
        }

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
