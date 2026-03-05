#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "common.hpp"
#include "board.hpp"
#include "tetro.hpp"

class Renderer {
public:
    Renderer();
    ~Renderer();
    SDL_Renderer *get_renderer();
    SDL_Texture *get_canvas();
    void draw_board(std::array<std::array<Cell, COLUMNS>, ROWS> &board);
    void draw_tetro(Tetro &tetro, std::array<std::array<Cell, COLUMNS>, ROWS> &board);
    void draw_reflection(std::array<std::array<Cell, COLUMNS>, ROWS> &cells, Tetro &tetro);
private:
    SDL_Window *window;
    SDL_Renderer *rnd;
    SDL_Texture *canvas;
    void draw_border();
};

#endif
