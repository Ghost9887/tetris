#include "board.hpp"

Board::Board() : board()
{
    for (int row = 0; row < ROWS; row++) {
        for (int column = 0; column < COLUMNS; column++) {
            board[row][column] = create_cell(column * CELL_SIZE + X_PADDING, row * CELL_SIZE + Y_PADDING);
        }
    }
}

std::array<std::array<Cell, COLUMNS>, ROWS> &Board::get_board() {
    return board;
}
