#ifndef COMMON_HPP
#define COMMON_HPP

#include <iostream>
#include <vector>
#include <memory>
#include <array>
#include <ctime>
#include <cstdlib>
#include <random>
#include <queue>
#include <optional>
#include "SDL2/SDL.h"

#define FPS 60
#define FRAME_TIME 1000 / FPS
#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 800
//MAIN GRID
#define ROWS 20
#define COLUMNS 10
#define CELL_SIZE 30
#define X_PADDING (SCREEN_WIDTH / 2) - ((COLUMNS * CELL_SIZE) / 2)
#define Y_PADDING (SCREEN_HEIGHT / 2) - ((ROWS * CELL_SIZE) / 2)

//NEXT TETROS GRID
#define NEXT_CELL_SIZE 25
#define X_NEXT_PADDING (SCREEN_WIDTH / 2) + (((COLUMNS * CELL_SIZE) / 2) + CELL_SIZE * 2)
#define Y_NEXT_PADDING (SCREEN_HEIGHT / 2) - ((ROWS * CELL_SIZE) / 2)
#define AMOUNT_OF_NEXT_TETROS 5
#define NEXT_ROWS 4 * AMOUNT_OF_NEXT_TETROS
#define NEXT_COLUMNS 10

typedef enum {
    Rotation,
    Down,
    Right,
    Left
}Direction;

#endif
