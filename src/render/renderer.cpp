#include "renderer.hpp"

Renderer::Renderer() :
    window(nullptr), rnd(nullptr), canvas(nullptr)
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

    rnd = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED
    );

    if (rnd == nullptr) 
        std::cout << "Failed to create renderer!" << '\n'; 

    canvas = SDL_CreateTexture(
        rnd,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_TARGET,
        SCREEN_WIDTH,
        SCREEN_HEIGHT
    );

    if (canvas == nullptr)
        std::cout << "Failed to create canvas!" << '\n';
}

SDL_Renderer *Renderer::get_renderer() {
    return rnd;
}

SDL_Texture *Renderer::get_canvas() {
    return canvas;
}

void Renderer::draw_border() {
    SDL_SetRenderDrawColor(rnd, 255, 255, 255, 255);
    SDL_Rect rect = { X_PADDING, Y_PADDING, CELL_SIZE * COLUMNS, CELL_SIZE * ROWS };
    SDL_RenderDrawRect(rnd, &rect);
}

void Renderer::draw_board(std::array<std::array<Cell, COLUMNS>, ROWS> &board) {
    for (int row = 0; row < ROWS; row++) {
        for (int column = 0; column < COLUMNS; column++) {
            if (board[row][column].active) {
                SDL_SetRenderDrawColor(rnd, board[row][column].colour.r, board[row][column].colour.g, board[row][column].colour.b, board[row][column].colour.a);
                SDL_RenderFillRect(rnd, &board[row][column].rect);
            }else {
                SDL_SetRenderDrawColor(rnd, 70, 70, 70, 255);
                SDL_RenderDrawRect(rnd, &board[row][column].rect);
            }
        }
    }
    draw_border();
}

void Renderer::draw_tetro(Tetro &tetro, std::array<std::array<Cell, COLUMNS>, ROWS> &board) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (tetro.get_value_in_shape(i, j) == 1) {
                SDL_SetRenderDrawColor(rnd, tetro.get_colour().r, tetro.get_colour().g, tetro.get_colour().b, tetro.get_colour().a);
                SDL_RenderFillRect(rnd, &board[tetro.get_row() + i][tetro.get_column() + j].rect);
            }
        }
    }
}

void Renderer::draw_reflection(std::array<std::array<Cell, COLUMNS>, ROWS> &board, Tetro &tetro) {
    Tetro temp_tetro = tetro;
    temp_tetro.hard_drop(board);
    SDL_Rect rect = { temp_tetro.get_row(), temp_tetro.get_column(), CELL_SIZE, CELL_SIZE };
    SDL_SetRenderDrawColor(rnd, temp_tetro.get_colour().r, temp_tetro.get_colour().g, temp_tetro.get_colour().b, temp_tetro.get_colour().a);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (temp_tetro.get_value_in_shape(i, j) == 1) {
                SDL_RenderDrawRect(rnd, &board.at(temp_tetro.get_row() + i).at(temp_tetro.get_column() + j).rect);
            }
        }
    }
}

void Renderer::draw_reserved_tetro(Tetro &tetro) {
}

void Renderer::draw_next_tetros(std::queue<Tetro> &next_tetros) {
}

Renderer::~Renderer() {
    SDL_DestroyRenderer(rnd);
    SDL_DestroyWindow(window);
    SDL_DestroyTexture(canvas);
    rnd = nullptr;
    window = nullptr;
    canvas = nullptr;
    SDL_Quit();
}
