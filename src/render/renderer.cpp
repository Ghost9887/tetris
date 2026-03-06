#include "renderer.hpp"

Renderer::Renderer() :
    window(nullptr), rnd(nullptr), canvas(nullptr), font(nullptr)
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
    
    if (TTF_Init() == -1) {
        std::cout << "TTF_Init error: " << TTF_GetError() << std::endl;
    }

    font = TTF_OpenFont("../fonts/font.ttf", FONT_SIZE);

    if (!font) {
        std::cout << "SDL could not find font!\n";
    }
}

SDL_Renderer *Renderer::get_renderer() {
    return rnd;
}

SDL_Texture *Renderer::get_canvas() {
    return canvas;
}

TTF_Font *Renderer::get_font() {
    return font;
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

void Renderer::draw_next_tetros(std::queue<Tetro> &next_tetros, std::array<std::array<Cell, NEXT_COLUMNS>, NEXT_ROWS> &next_board) {
    std::queue<Tetro> temp = next_tetros;
    int absolute_row = 0;
    for (int i = 0; i < AMOUNT_OF_NEXT_TETROS; i++) {
        Tetro tetro = temp.front();
        temp.pop();

        SDL_SetRenderDrawColor(rnd, tetro.get_colour().r, tetro.get_colour().g, tetro.get_colour().b, tetro.get_colour().a);
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                if (tetro.get_value_in_shape(j, k) == 1) {
                    SDL_RenderFillRect(rnd, &next_board.at(absolute_row + j).at(k).rect);
                }
            }
        }
        absolute_row += 4;
    }
}

void Renderer::draw_reserved_tetro(std::optional<Tetro> &tetro, std::array<std::array<Cell, RESERVE_COLUMNS>, RESERVE_ROWS> &reserved_board) {
    if (tetro.has_value()) {
        SDL_SetRenderDrawColor(rnd, tetro.value().get_colour().r, tetro.value().get_colour().g, tetro.value().get_colour().b, tetro.value().get_colour().a);
        for (int row = 0; row < RESERVE_ROWS; row++) {
            for (int column = 0; column < RESERVE_COLUMNS; column++) {
                if (tetro.value().get_value_in_shape(row, column) == 1) {
                    SDL_RenderFillRect(rnd, &reserved_board.at(row).at(column).rect);
                }
            }
        }
    }
}

//TODO: REFACTOR
void Renderer::draw_ui(int score, int level) {
    //score
    std::string text = "Score: " + std::to_string(score);
    SDL_Rect rect = { X_SCORE_PADDING, Y_SCORE_PADDING, static_cast<int>(text.length() * FONT_SIZE), 50 };
    SDL_Color text_colour = { 255, 255, 255, 255 };
    SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), text_colour);
    SDL_Texture *text_texture = SDL_CreateTextureFromSurface(rnd, surface);
    SDL_RenderCopy(rnd, text_texture, NULL, &rect);

    //next tetros
    std::string next_text = "Next";
    SDL_Rect next_rect = { X_NEXT_PADDING, Y_NEXT_PADDING - 40, static_cast<int>(next_text.length() * FONT_SIZE + 20), 50 };
    SDL_Surface *next_surface = TTF_RenderText_Solid(font, next_text.c_str(), text_colour);
    SDL_Texture *next_text_texture = SDL_CreateTextureFromSurface(rnd, next_surface);
    SDL_RenderCopy(rnd, next_text_texture, NULL, &next_rect);

    //level
    std::string level_text = "Level: " + std::to_string(level);
    SDL_Rect level_rect = { X_LEVEL_PADDING,  Y_LEVEL_PADDING, static_cast<int>(level_text.length()) * FONT_SIZE, 50 };
    SDL_Surface *level_surface = TTF_RenderText_Solid(font, level_text.c_str(), text_colour);   
    SDL_Texture *level_texture = SDL_CreateTextureFromSurface(rnd, level_surface);
    SDL_RenderCopy(rnd, level_texture, NULL, &level_rect);

    SDL_FreeSurface(surface);
    SDL_FreeSurface(next_surface);
    SDL_FreeSurface(level_surface);
    SDL_DestroyTexture(text_texture);
    SDL_DestroyTexture(next_text_texture);
    SDL_DestroyTexture(level_texture);

    text_texture = nullptr;
    next_text_texture = nullptr;
    level_texture = nullptr;
    surface = nullptr;
    next_surface = nullptr;
    level_surface = nullptr;
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
