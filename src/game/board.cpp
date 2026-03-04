#include "board.hpp"

Board::Board() : cells()
{
    for (int y = 0; y < ROWS; y++) {
        std::vector<Cell> temp{0};
        for (int x = 0; x < COLUMNS; x++) {
            temp.push_back(create_cell(x * CELL_SIZE + X_PADDING, y * CELL_SIZE + Y_PADDING));
        }
        cells.push_back(temp);
    }
}

std::vector<std::vector<Cell>> &Board::get_board() {
    return cells;
}

void Board::draw_border(SDL_Renderer *rnd) {
    SDL_SetRenderDrawColor(rnd, 255, 255, 255, 255);
    SDL_Rect rect = { X_PADDING, Y_PADDING, CELL_SIZE * COLUMNS, CELL_SIZE * ROWS };
    SDL_RenderDrawRect(rnd, &rect);
}

void Board::draw_board(SDL_Renderer *rnd) {
    SDL_SetRenderDrawColor(rnd, 100, 100, 100, 255);
    for (int y = 0; y < ROWS; y++) {
        for (int x = 0; x < COLUMNS; x++) {
            SDL_RenderDrawRect(rnd, &cells.at(y).at(x).rect);
            cells.at(y).at(x).active = false;
        }
    }
    draw_border(rnd);
}
