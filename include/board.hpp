#ifndef BOARD_HPP
#define BOARD_HPP

#include "common.hpp"
#include "cell.hpp"

class Board {
public:
    Board();
    ~Board() = default;
    void draw_board(SDL_Renderer *rnd);
    void draw_border(SDL_Renderer *rnd);
    std::vector<std::vector<Cell>> &get_board();
private:
    std::vector<std::vector<Cell>> cells;
};

#endif
