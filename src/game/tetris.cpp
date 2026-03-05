#include "tetris.hpp"

bool clear_row(std::array<std::array<Cell, COLUMNS>, ROWS> &board) {
    return false;
}

void run(Renderer *renderer) {
    SDL_Renderer *rnd = renderer->get_renderer();
    SDL_Texture *canvas = renderer->get_canvas();
    
    Board board;

    SDL_Event event;
    bool running = true;
    bool moved_down;
    
    Uint32 lastFallTime = SDL_GetTicks(); 
    const Uint32 fallDelay = 500;
    
    Player player(Tetro::create_random_tetro());

    while (running) {
        if (player.get_current_tetro().is_fixed()) {
            player.get_current_tetro().move_tetro_to_board(board.get_board());
            if (clear_row(board.get_board())) {
            }
            player.set_current_tetro(Tetro::create_random_tetro());
        }

        moved_down = false;
        Uint32 frame_start = SDL_GetTicks();

        while(SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                running = false;
            }else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_SPACE:
                        player.get_current_tetro().hard_drop(board.get_board());
                        moved_down = true;
                        break;
                    case SDLK_r:
                        player.get_current_tetro().rotate(board.get_board());
                        break;
                    case SDLK_LEFT:
                        player.get_current_tetro().move(Left, board.get_board());
                        break;
                    case SDLK_RIGHT:
                        player.get_current_tetro().move(Right, board.get_board());
                        break;
                    case SDLK_DOWN:
                        if (!moved_down) {
                            player.get_current_tetro().move(Down, board.get_board());
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

        renderer->draw_tetro(player.get_current_tetro(), board.get_board());
        renderer->draw_board(board.get_board());
        renderer->draw_reflection(board.get_board(), player.get_current_tetro());

        Uint32 now = SDL_GetTicks();
        if (now - lastFallTime >= fallDelay && !moved_down) {
            player.get_current_tetro().move(Down, board.get_board());
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
