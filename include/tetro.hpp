#ifndef TETRO_HPP
#define TETRO_HPP

#include "common.hpp"
#include "board.hpp"

class Tetro{
public:
    Tetro(char shape);
    ~Tetro() = default;
    Tetro *get_tetro();
    void draw_tetro(SDL_Renderer *rnd, std::vector<std::vector<Cell>> *cells);
    bool not_out_of_bounds(Direction dir);
    void move_down();
private:
    int column; //x
    int row; //y
    char shape;
    SDL_Color colour;
};

#endif
