#ifndef TETRO_HPP
#define TETRO_HPP

#include "common.hpp"
#include "board.hpp"

class Tetro{
public:
    Tetro(char id);
    ~Tetro() = default;
    static Tetro create_random_tetro();
    static void draw_tetros(const std::vector<Tetro> &tetros, SDL_Renderer *rnd, std::vector<std::vector<Cell>> &cells);
    static void move_tetros_down(std::vector<Tetro> &tetros);
    void move(Direction dir, const std::vector<Tetro> &tetros);
    void rotate(const std::vector<Tetro> &tetros);
    void hard_drop(const std::vector<Tetro> &tetros);
    bool is_fixed();    
    void draw_reflection(const std::vector<std::vector<Cell>> &cells, const std::vector<Tetro> &tetros, SDL_Renderer *rnd);
    int get_value_in_shape(int i, int j);
    void set_value_in_shape(int i, int j, int value);
    int get_row();
    int get_column();
private:
    int column; //x
    int row; //y
    char id;
    std::array<std::array<int, 4>, 4> shape;
    SDL_Color colour;
    bool check_collision(Direction dir, const std::vector<Tetro> &tetros);
    bool fixed;
    int rotation_state;
};

#endif
