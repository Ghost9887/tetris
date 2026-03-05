#ifndef CELL_HPP
#define CELL_HPP

#include "common.hpp"

typedef struct {
public:
    SDL_Rect rect;
    bool active;
    SDL_Color colour;
}Cell;

Cell create_cell(int x, int y);

#endif
