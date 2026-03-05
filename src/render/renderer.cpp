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
    SDL_SetRenderDrawColor(rnd, 100, 100, 100, 255);
    for (int row = 0; row < ROWS; row++) {
        for (int column = 0; column < COLUMNS; column++) {
            SDL_RenderDrawRect(rnd, &board[row][column].rect);
        }
    }
    draw_border();
}

void Renderer::draw_tetros(std::vector<Tetro> &tetros, std::array<std::array<Cell, COLUMNS>, ROWS> &board) {
    for (int t = 0; t < tetros.size(); t++) {
        SDL_SetRenderDrawColor(rnd, tetros.at(t).get_colour().r, tetros.at(t).get_colour().g, tetros.at(t).get_colour().b, tetros.at(t).get_colour().a);
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (tetros.at(t).get_value_in_shape(i, j) == 1) {
                    SDL_RenderFillRect(rnd, &board.at(tetros.at(t).get_row() + i).at(tetros.at(t).get_column() + j).rect);
                }
            }
        }
    }
}

void Renderer::draw_reflection(std::array<std::array<Cell, COLUMNS>, ROWS> &board, std::vector<Tetro> &tetros, Tetro &tetro) {
    Tetro temp_tetro = tetro;
    temp_tetro.hard_drop(tetros);
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

Renderer::~Renderer() {
    SDL_DestroyRenderer(rnd);
    SDL_DestroyWindow(window);
    SDL_DestroyTexture(canvas);
    rnd = nullptr;
    window = nullptr;
    canvas = nullptr;
    SDL_Quit();
}
