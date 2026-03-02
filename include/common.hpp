#ifndef COMMON_HPP
#define COMMON_HPP

#include <iostream>
#include <vector>
#include "SDL2/SDL.h"
#include "renderer.hpp"

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 800
#define ROWS 20
#define COLUMNS 10
#define CELL_SIZE 30
#define X_PADDING (SCREEN_WIDTH / 2) - ((COLUMNS * CELL_SIZE) / 2)
#define Y_PADDING (SCREEN_HEIGHT / 2) - ((ROWS * CELL_SIZE) / 2)

#endif
