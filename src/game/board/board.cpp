#include "board.hpp"

Board::Board() : cells()
{
    for (int y = 0; y < ROWS; y++) {
        for (int x = 0; x < COLUMNS; x++) {
            cells.push_back(create_cell(x * CELL_SIZE + X_PADDING, y * CELL_SIZE + Y_PADDING));
        }
    }
}

std::vector<Cell> *Board::get_cells() {
    return &cells;
}

void Board::draw_board(SDL_Renderer *rnd) {
    SDL_SetRenderDrawColor(rnd, 255, 255, 255, 255);
    for (Cell cell : cells) {
        SDL_RenderDrawRect(rnd, &cell.rect);
    }
}
