#ifndef TETRO_HPP
#define TETRO_HPP

#include "common.hpp"
#include "board.hpp"

class Tetro{
public:
    Tetro(char id);
    ~Tetro() = default;
    static Tetro create_random_tetro();
    void move(Direction dir, const std::array<std::array<Cell, COLUMNS>, ROWS> &board);
    void rotate(const std::array<std::array<Cell, COLUMNS>, ROWS> &board);
    void hard_drop(const std::array<std::array<Cell, COLUMNS>, ROWS> &board);
    void move_tetro_to_board(std::array<std::array<Cell, COLUMNS>, ROWS> &board);
    bool is_fixed();    
    int get_value_in_shape(int i, int j);
    void set_value_in_shape(int i, int j, int value);
    int get_row();
    int get_column();
    void add_row();
    SDL_Color get_colour();
private:
    int column; //x
    int row; //y
    char id;
    std::array<std::array<int, 4>, 4> shape;
    SDL_Color colour;
    bool check_collision(Direction dir, const std::array<std::array<Cell, COLUMNS>, ROWS> &board);
    bool fixed;
    int rotation_state;
};

#endif
