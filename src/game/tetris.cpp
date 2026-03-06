#include "tetris.hpp"

int clear_row(std::array<std::array<Cell, COLUMNS>, ROWS> &board) {
    int amount_of_rows_cleared = 0;
    for (int row = 0; row < ROWS; row++) {
        int count = 0;
        for (int column = 0; column < COLUMNS; column++) {
            if (!board[row][column].active) count++;
        }
        if (count == 0) {
            for (int i = row; i >= 1;i--) {
                for (int j = 0; j < COLUMNS; j++) {
                    board[i][j].colour = board[i - 1][j].colour;
                    board[i][j].active = board[i - 1][j].active;
                }
            }
        }
    }
    return amount_of_rows_cleared;
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
    player.get_next_tetro();

    while (running) {
        if (player.get_current_tetro().is_fixed()) {
            player.add_score(1);
            player.get_current_tetro().move_tetro_to_board(board.get_board());
            int count = clear_row(board.get_board());
            if (count > 0) {
                if (count == 1) {
                    player.add_score(40);
                }else if (count == 2) {
                    player.add_score(100);
                }else if (count == 3) {
                    player.add_score(300);
                }else {
                    player.add_score(1200);
                }
            }
            player.get_next_tetro();
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
                        player.add_score(1);
                        break;
                    case SDLK_UP:
                        player.get_current_tetro().rotate(board.get_board());
                        break;
                    case SDLK_c:
                        player.reserve_current_tetro();
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
        renderer->draw_next_tetros(player.get_next_tetros(), board.get_next_board());
        renderer->draw_reserved_tetro(player.get_reserved_tetro(), board.get_reserved_board());
        renderer->draw_ui(player.get_score());

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
