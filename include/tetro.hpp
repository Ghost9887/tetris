#ifndef TETRO_HPP
#define TETRO_HPP

#include "common.hpp"
#include "board.hpp"

class Tetro{
public:
    Tetro(char id);
    ~Tetro() = default;
    Tetro *get_tetro();
    static Tetro create_random_tetro();
    static void draw_tetros(const std::vector<Tetro> &tetros, SDL_Renderer *rnd, std::vector<std::vector<Cell>> &cells);
    static void move(Tetro &tetro, Direction dir, const std::vector<Tetro> &tetros);
    void set_fixed(bool value);
    bool is_fixed();
private:
    int column; //x
    int row; //y
    char id;
    std::array<std::array<int, 4>, 4> shape;
    SDL_Color colour;
    bool not_out_of_bounds(Direction dir, Tetro &tetro, const std::vector<Tetro> &tetros);
    bool fixed;
};

#endif
