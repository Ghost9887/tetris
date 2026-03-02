#ifndef BOARD_HPP
#define BOARD_HPP

#include "common.hpp"
#include "cell.hpp"

class Board {
public:
    Board();
    ~Board() = default;
    void draw_board(SDL_Renderer *rnd);
    std::vector<Cell> *get_cells();
private:
    std::vector<Cell> cells;
};

#endif
