#include "board.hpp"

Board::Board() : board(), next_board(), reserved_board()
{
    for (int row = 0; row < ROWS; row++) {
        for (int column = 0; column < COLUMNS; column++) {
            board.at(row).at(column) = create_cell(column * CELL_SIZE + X_PADDING, row * CELL_SIZE + Y_PADDING);
        }
    }

    int count = 0;
    int Y_PADDING_EXTRA = 0;
    for (int row = 0; row < NEXT_ROWS; row++) {
        if (count % 4 == 0) {
            Y_PADDING_EXTRA += NEXT_TETRO_PADDING;
        }
        for (int column = 0; column < NEXT_COLUMNS; column++) {
            next_board.at(row).at(column) = create_cell(
                column * NEXT_CELL_SIZE + X_NEXT_PADDING,
                row * NEXT_CELL_SIZE + Y_NEXT_PADDING + Y_PADDING_EXTRA
            );
        }
        count++;
    }

    for (int row = 0; row < RESERVE_ROWS; row++) {
        for (int column = 0; column < RESERVE_COLUMNS; column++) {
            reserved_board.at(row).at(column) = create_cell(
                column * NEXT_CELL_SIZE + X_RESERVE_PADDING,
                row * NEXT_CELL_SIZE + Y_RESERVE_PADDING
            );
        }
    }
}

std::array<std::array<Cell, COLUMNS>, ROWS> &Board::get_board() {
    return board;
}

std::array<std::array<Cell, NEXT_COLUMNS>, NEXT_ROWS> &Board::get_next_board() {
    return next_board;
}

std::array<std::array<Cell, RESERVE_COLUMNS>, RESERVE_ROWS> &Board::get_reserved_board() {
    return reserved_board;
}
