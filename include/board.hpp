#ifndef BOARD_HPP
#define BOARD_HPP

#include "common.hpp"
#include "cell.hpp"

class Board {
public:
    Board();
    ~Board() = default;
    std::array<std::array<Cell, COLUMNS>, ROWS> &get_board();
private:
    std::array<std::array<Cell, COLUMNS>, ROWS> board;
};

#endif
