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
    void move(Direction dir, const std::vector<Tetro> &tetros);
    void rotate(const std::vector<Tetro> &tetros);
    void hard_drop(const std::vector<Tetro> &tetros);
    void set_fixed(bool value);
    bool is_fixed();    
    void draw_reflection(const std::vector<std::vector<Cell>> &cells, const std::vector<Tetro> &tetros, SDL_Renderer *rnd);
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
