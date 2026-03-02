#include "tetro.hpp"

Tetro::Tetro(char shape) :
    column(COLUMNS / 2), row(0), shape(shape), colour() 
{
    switch (shape) {
        case 'i':
            colour = { 0, 255, 255, 255 };
            break;
        case 'o':
            colour = { 255, 255, 0, 255 };
            break;
        case 't':
            colour = { 255, 20, 147, 255 };
            break;
        case 'j':
            colour = { 0, 0, 255, 255 };
            break;
        case 'l':
            colour = { 255, 140, 0, 255 };
            break;
        case 's':
            colour = { 0, 255, 0, 255 };
            break;
        case 'z':
            colour = { 255, 0, 0, 255 };
            break;
        default: break;
    }
}

void Tetro::draw_tetro(SDL_Renderer *rnd, std::vector<std::vector<Cell>> *cells) {
    SDL_SetRenderDrawColor(rnd, colour.r, colour.g, colour.b, colour.a);
    SDL_RenderFillRect(rnd, &cells->at(row).at(column).rect);
}

bool Tetro::not_out_of_bounds(Direction dir) {
    int next_row = row;
    int next_column = column;
    switch (dir) {
        case Down:
            next_row++;
            break;
        case Right:
            next_column++;
            break;
        case Left:
            next_column--;
            break;
        default: break;
    }
    std::cout << "Row: " << row << '\n';
    return 
        next_row < ROWS
        && next_row > 0
        && next_column < COLUMNS
        && next_column > 0;
}

void Tetro::move_down() {
    if (not_out_of_bounds(Down)) row++;
}

