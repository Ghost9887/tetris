#ifndef CELL_HPP
#define CELL_HPP

#include "common.hpp"

typedef struct {
    SDL_Rect rect;
    bool empty;
}Cell;

Cell create_cell(int x, int y);

#endif
