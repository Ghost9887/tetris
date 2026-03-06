#include "tetro.hpp"

Tetro::Tetro(char id) :
    column(COLUMNS / 2), row(0), id(id), shape(), colour(), fixed(false), rotation_state(1) 
{
    switch (id) {
        case 'i':
            colour = { 0, 255, 255, 255 };
            shape = {{
                {0, 1, 0, 0},
                {0, 1, 0, 0},
                {0, 1, 0, 0},
                {0, 1, 0, 0}
            }};
            break;
        case 'o':
            colour = { 255, 255, 0, 255 };
            shape = {{
                {0, 0, 0, 0},
                {0, 1, 1, 0},
                {0, 1, 1, 0},
                {0, 0, 0, 0}
            }};
            break;
        case 't':
            colour = { 255, 20, 147, 255 };
            shape = {{
                {0, 1, 0, 0},
                {1, 1, 1, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0}
            }};
            break;
        case 'j':
            colour = { 0, 0, 255, 255 };
            shape = {{
                {0, 1, 0, 0},
                {0, 1, 0, 0},
                {1, 1, 0, 0},
                {0, 0, 0, 0}
            }};
            break;
        case 'l':
            colour = { 255, 140, 0, 255 };
            shape = {{
                {1, 0, 0, 0},
                {1, 0, 0, 0},
                {1, 1, 0, 0},
                {0, 0, 0, 0}
            }};
            break;
        case 's':
            colour = { 0, 255, 0, 255 };
            shape = {{
                {0, 1, 1, 0},
                {1, 1, 0, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0}
            }};
            break;
        case 'z':
            colour = { 255, 0, 0, 255 };
            shape = {{
                {1, 1, 0, 0},
                {0, 1, 1, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0}
            }};
            break;
        default: break;
    }
}

Tetro Tetro::create_random_tetro() {
    static std::mt19937 rng(std::random_device{}());
    static std::uniform_int_distribution<int> dist(1, 7);

    switch (dist(rng)) {
        case 1: return Tetro('i');
        case 2: return Tetro('o');
        case 3: return Tetro('z');
        case 4: return Tetro('s');
        case 5: return Tetro('l');
        case 6: return Tetro('j');
        case 7: return Tetro('t');
    }

    return Tetro('i');
}


bool Tetro::check_collision(Direction dir, const std::array<std::array<Cell, COLUMNS>, ROWS> &board) {
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
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (shape[i][j] == 1) {
                int current_next_row = next_row + i;
                int current_next_column = next_column + j;
                //bounds
                if (current_next_row >= ROWS || current_next_column < 0 || current_next_column >= COLUMNS ) {
                    if (dir == Down) {
                        fixed = true;
                    }
                    return true;
                }
                //other tetros
                
                else if (board[current_next_row][current_next_column].active) {
                    if (dir == Down) {
                        fixed = true;
                    }
                    return true;
                }
                
            }
        }
    }

    return false;
}

void Tetro::move_tetro_to_board(std::array<std::array<Cell, COLUMNS>, ROWS> &board) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (shape[i][j] == 1) {
                board[row + i][column + j].active = true;
                board[row + i][column + j].colour = colour;
            }
        }
    }
}

void Tetro::move(Direction dir, const std::array<std::array<Cell, COLUMNS>, ROWS> &board) {
    switch (dir) {
        case Down:
            if (!check_collision(Down, board)) row++;
            break;
        case Right:
            if (!check_collision(Right, board)) column++;
            break;
        case Left:
            if (!check_collision(Left, board)) column--;
            break;
        default: break;
    }
}

void Tetro::hard_drop(const std::array<std::array<Cell, COLUMNS>, ROWS> &board) {
    while (!fixed) {
        if (!check_collision(Down, board)) row++;
    }
}

bool Tetro::is_fixed() {
    return fixed;
}

int Tetro::get_value_in_shape(int i, int j) {
    return shape[i][j];
}

void Tetro::set_value_in_shape(int i, int j, int value) {
    shape[i][j] = value;
}

int Tetro::get_row() {
    return row;
}

int Tetro::get_column() {
    return column;
}

void Tetro::set_row(int new_row) {
    row = new_row;
}

void Tetro::set_column(int new_column) {
    column = new_column;
}

void Tetro::add_row() {
    row++;
}

SDL_Colour Tetro::get_colour() {
    return colour;
}

void Tetro::rotate(const std::array<std::array<Cell, COLUMNS>, ROWS> &board) {

    int original_row = row;
    int original_column = column;
    std::array<std::array<int, 4>, 4> original_shape = shape;

    if (id == 'i') {
        switch (rotation_state) {
            case 1:
                shape = {{
                    {0, 0, 0, 0},
                    {1, 1, 1, 1},
                    {0, 0, 0, 0},
                    {0, 0, 0, 0}
                }};
                if (!check_collision(Rotation, board)) {
                    rotation_state = 2;
                    return;
                }
                break;
            case 2:
                shape = {{
                    {0, 1, 0, 0},
                    {0, 1, 0, 0},
                    {0, 1, 0, 0},
                    {0, 1, 0, 0}
                }};
                if (!check_collision(Rotation, board)) {
                    rotation_state = 1;
                    return;
                }
                break;
            default: break;
        }
    }
    else if (id == 'j') {
        switch (rotation_state) {
            case 1:
                shape = {{
                    {1, 0, 0, 0},
                    {1, 1, 1, 0},
                    {0, 0, 0, 0},
                    {0, 0, 0, 0}
                }};
                if (!check_collision(Rotation, board)) {
                    rotation_state = 2;
                    return;
                }
                break;
            case 2:
                shape = {{
                    {0, 1, 1, 0},
                    {0, 1, 0, 0},
                    {0, 1, 0, 0},
                    {0, 0, 0, 0}
                }};
                if (!check_collision(Rotation, board)) {
                    rotation_state = 3;
                    return;
                }
                break;
            case 3:
                shape = {{
                    {1, 1, 1, 0},
                    {0, 0, 1, 0},
                    {0, 0, 0, 0},
                    {0, 0, 0, 0}
                }};
                if (!check_collision(Rotation, board)) {
                    rotation_state = 4;
                    return;
                }
                break;
            case 4:
                shape = {{
                    {0, 1, 0, 0},
                    {0, 1, 0, 0},
                    {1, 1, 0, 0},
                    {0, 0, 0, 0}
                }};
                if (!check_collision(Rotation, board)) {
                    rotation_state = 1;
                    return;
                }
                break;
            default: break;
        }
    }
    else if (id == 'l') {
        switch (rotation_state) {
            case 1:
                shape = {{
                    {0, 0, 1, 0},
                    {1, 1, 1, 0},
                    {0, 0, 0, 0},
                    {0, 0, 0, 0}
                }};
                if (!check_collision(Rotation, board)) {
                    rotation_state = 2;
                    return;
                }
                break;
            case 2:
                shape = {{
                    {1, 1, 0, 0},
                    {0, 1, 0, 0},
                    {0, 1, 0, 0},
                    {0, 0, 0, 0}
                }};
                if (!check_collision(Rotation, board)) {
                    rotation_state = 3;
                    return;
                }
                break;
            case 3:
                shape = {{
                    {1, 1, 1, 0},
                    {1, 0, 0, 0},
                    {0, 0, 0, 0},
                    {0, 0, 0, 0}
                }};
                if (!check_collision(Rotation, board)) {
                    rotation_state = 4;
                    return;
                }
                break;
            case 4:
                shape = {{
                    {1, 0, 0, 0},
                    {1, 0, 0, 0},
                    {1, 1, 0, 0},
                    {0, 0, 0, 0}
                }};
                if (!check_collision(Rotation, board)) {
                    rotation_state = 1;
                    return;
                }
                break;
            default: break;
        }
    }
    else if (id == 'z') {
        switch (rotation_state) {
            case 1:
                shape = {{
                    {0, 1, 0, 0},
                    {1, 1, 0, 0},
                    {1, 0, 0, 0},
                    {0, 0, 0, 0}
                }};
                if (!check_collision(Rotation, board)) {
                    rotation_state = 2;
                    return;
                }
                break;
            case 2:
                shape = {{
                    {1, 1, 0, 0},
                    {0, 1, 1, 0},
                    {0, 0, 0, 0},
                    {0, 0, 0, 0}
                }};
                if (!check_collision(Rotation, board)) {
                    rotation_state = 1;
                    return;
                }
                break;
            default: break;
        }
    }
    else if (id == 's') {
        switch (rotation_state) {
            case 1:
                shape = {{
                    {1, 0, 0, 0},
                    {1, 1, 0, 0},
                    {0, 1, 0, 0},
                    {0, 0, 0, 0}
                }};
                if (!check_collision(Rotation, board)) {
                    rotation_state = 2;
                    return;
                }
                break;
            case 2:
                shape = {{
                    {0, 1, 1, 0},
                    {1, 1, 0, 0},
                    {0, 0, 0, 0},
                    {0, 0, 0, 0}
                }};
                if (!check_collision(Rotation, board)) {
                    rotation_state = 1;
                    return;
                }
                break;
            default: break;
        }
    }
    else if (id == 't') {
        switch (rotation_state) {
            case 1:
                shape = {{
                    {1, 0, 0, 0},
                    {1, 1, 0, 0},
                    {1, 0, 0, 0},
                    {0, 0, 0, 0}
                }};
                if (!check_collision(Rotation, board)) {
                    rotation_state = 2;
                    return;
                }
                break;
            case 2:
                shape = {{
                    {1, 1, 1, 0},
                    {0, 1, 0, 0},
                    {0, 0, 0, 0},
                    {0, 0, 0, 0}
                }};
                if (!check_collision(Rotation, board)) {
                    rotation_state = 3;
                    return;
                }
                break;
            case 3:
                shape = {{
                    {0, 1, 0, 0},
                    {1, 1, 0, 0},
                    {0, 1, 0, 0},
                    {0, 0, 0, 0}
                }};
                if (!check_collision(Rotation, board)) {
                    rotation_state = 4;
                    return;
                }
                break;
            case 4:
                shape = {{
                    {0, 1, 0, 0},
                    {1, 1, 1, 0},
                    {0, 0, 0, 0},
                    {0, 0, 0, 0}
                }};
                if (!check_collision(Rotation, board)) {
                    rotation_state = 1;
                    return;
                }
                break;
            default: break;
        }
    }

    row = original_row;
    column = original_column;
    shape = original_shape;
}
