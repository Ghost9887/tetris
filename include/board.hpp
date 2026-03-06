#ifndef BOARD_HPP
#define BOARD_HPP

#include "common.hpp"
#include "cell.hpp"

class Board {
public:
    Board();
    ~Board() = default;
    std::array<std::array<Cell, COLUMNS>, ROWS> &get_board();
    std::array<std::array<Cell, NEXT_COLUMNS>, NEXT_ROWS> &get_next_board();
    std::array<std::array<Cell, RESERVE_COLUMNS>, RESERVE_ROWS> &get_reserved_board();
private:
    std::array<std::array<Cell, COLUMNS>, ROWS> board;
    std::array<std::array<Cell, NEXT_COLUMNS>, NEXT_ROWS> next_board;
    std::array<std::array<Cell, RESERVE_COLUMNS>, RESERVE_ROWS> reserved_board;
};

#endif
