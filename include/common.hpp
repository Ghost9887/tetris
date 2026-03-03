#ifndef COMMON_HPP
#define COMMON_HPP

#include <iostream>
#include <vector>
#include <memory>
#include <array>
#include <ctime>
#include <cstdlib>
#include "SDL2/SDL.h"
#include "renderer.hpp"

#define FPS 60
#define FRAME_TIME 1000 / FPS
#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 800
#define ROWS 20
#define COLUMNS 10
#define CELL_SIZE 30
#define X_PADDING (SCREEN_WIDTH / 2) - ((COLUMNS * CELL_SIZE) / 2)
#define Y_PADDING (SCREEN_HEIGHT / 2) - ((ROWS * CELL_SIZE) / 2)

typedef enum {
    Down,
    Right,
    Left
}Direction;

#endif
