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
#include "SDL2/SDL_ttf.h"

#define FPS 60
#define FRAME_TIME 1000 / FPS
#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 800
#define FONT_SIZE 16

//TODO: REFACTOR 
//MAIN GRID
#define ROWS 20
#define COLUMNS 10
#define CELL_SIZE 30
#define X_PADDING (SCREEN_WIDTH / 2) - ((COLUMNS * CELL_SIZE) / 2)
#define Y_PADDING (SCREEN_HEIGHT / 2) - ((ROWS * CELL_SIZE) / 2)

//NEXT TETROS GRID
#define X_NEXT_PADDING (SCREEN_WIDTH / 2) + (((COLUMNS * CELL_SIZE) / 2) + CELL_SIZE * 2)
#define Y_NEXT_PADDING (SCREEN_HEIGHT / 2) - ((ROWS * CELL_SIZE) / 2)
#define AMOUNT_OF_NEXT_TETROS 5
#define NEXT_ROWS 4 * AMOUNT_OF_NEXT_TETROS
#define NEXT_COLUMNS 4
#define NEXT_CELL_SIZE 20
#define NEXT_TETRO_PADDING 20

//RESERVE GRID
#define X_RESERVE_PADDING X_PADDING - (CELL_SIZE * 4)
#define Y_RESERVE_PADDING (SCREEN_HEIGHT / 2) - ((ROWS * CELL_SIZE) / 2)
#define RESERVE_ROWS 4
#define RESERVE_COLUMNS 4

//SCORE
#define X_SCORE_PADDING X_PADDING - (CELL_SIZE * 4)
#define Y_SCORE_PADDING (SCREEN_HEIGHT / 2) - ((ROWS * CELL_SIZE) / 2) - CELL_SIZE * 2

//LEVEL
#define X_LEVEL_PADDING X_SCORE_PADDING
#define Y_LEVEL_PADDING Y_SCORE_PADDING - CELL_SIZE - 20

typedef enum {
    Rotation,
    Down,
    Right,
    Left
}Direction;

#endif
