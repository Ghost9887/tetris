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
                {1, 1, 0, 0},
                {1, 1, 0, 0},
                {0, 0, 0, 0},
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

void Tetro::draw_tetros(const std::vector<Tetro> &tetros, SDL_Renderer *rnd, std::vector<std::vector<Cell>> &cells) {
    for (int t = 0; t < tetros.size(); t++) {
        SDL_SetRenderDrawColor(rnd, tetros.at(t).colour.r, tetros.at(t).colour.g, tetros.at(t).colour.b, tetros.at(t).colour.a);
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (tetros.at(t).shape[i][j] == 1) {
                    SDL_RenderFillRect(rnd, &cells.at(tetros.at(t).row + i).at(tetros.at(t).column + j).rect);
                    cells.at(tetros.at(t).row + i).at(tetros.at(t).column + j).active = true;
                }
            }
        }
    }
}

Tetro Tetro::create_random_tetro() {
    srand(time(0));
    int random_number = rand() % 7 + 1;

    switch (random_number) {
        case 1:
            return Tetro('i');
        case 2:
            return Tetro('o');
        case 3:
            return Tetro('z');
        case 4:
            return Tetro('s');
        case 5:
            return Tetro('l');
        case 6:
            return Tetro('j');
        case 7:
            return Tetro('t');
        default: return Tetro('i');
    }
}

bool Tetro::check_collision(Direction dir, const std::vector<Tetro> &tetros) {
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
                for (int t = 0; t < tetros.size() - 1; t++) {
                    for (int k = 0; k < 4; k++) {
                        for (int l = 0; l < 4; l++) {
                            if (tetros.at(t).shape[k][l] == 1) {
                                int tetro_row = tetros.at(t).row + k;
                                int tetro_column = tetros.at(t).column + l;
                                if (current_next_row == tetro_row && current_next_column == tetro_column) {
                                    if (dir == Down) {
                                        fixed = true;
                                    }
                                    return true;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return false;
}

void Tetro::move(Direction dir, const std::vector<Tetro> &tetros) {
    switch (dir) {
        case Down:
            if (!check_collision(Down, tetros)) row++;
            break;
        case Right:
            if (!check_collision(Right, tetros)) column++;
            break;
        case Left:
            if (!check_collision(Left, tetros)) column--;
            break;
        default: break;
    }
}

void Tetro::hard_drop(const std::vector<Tetro> &tetros) {
    while (!fixed) {
        if (!check_collision(Down, tetros)) row++;
    }
}

bool Tetro::is_fixed() {
    return fixed;
}

void Tetro::draw_reflection(const std::vector<std::vector<Cell>> &cells, const std::vector<Tetro> &tetros, SDL_Renderer *rnd) {
    Tetro temp_tetro = *this;
    while (!temp_tetro.check_collision(Down, tetros)) {
        temp_tetro.row++;
    } 
    SDL_Rect rect = { temp_tetro.row, temp_tetro.column, CELL_SIZE, CELL_SIZE };
    SDL_SetRenderDrawColor(rnd, temp_tetro.colour.r, temp_tetro.colour.g, temp_tetro.colour.b, temp_tetro.colour.a);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (temp_tetro.shape[i][j] == 1) {
                SDL_RenderDrawRect(rnd, &cells.at(temp_tetro.row + i).at(temp_tetro.column + j).rect);
            }
        }
    }
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


//TODO: Fix order is fucking me
void Tetro::move_tetros_down(std::vector<Tetro> &tetros) {
    for (int t = 0; t < tetros.size(); t++) {
        tetros.at(t).fixed = false;
        tetros.at(t).hard_drop(tetros);
    }
}

void Tetro::rotate(const std::vector<Tetro> &tetros) {

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
                if (!check_collision(Rotation, tetros)) {
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
                if (!check_collision(Rotation, tetros)) {
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
                if (!check_collision(Rotation, tetros)) {
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
                if (!check_collision(Rotation, tetros)) {
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
                if (!check_collision(Rotation, tetros)) {
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
                if (!check_collision(Rotation, tetros)) {
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
                if (!check_collision(Rotation, tetros)) {
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
                if (!check_collision(Rotation, tetros)) {
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
                if (!check_collision(Rotation, tetros)) {
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
                if (!check_collision(Rotation, tetros)) {
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
                if (!check_collision(Rotation, tetros)) {
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
                if (!check_collision(Rotation, tetros)) {
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
                if (!check_collision(Rotation, tetros)) {
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
                if (!check_collision(Rotation, tetros)) {
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
                if (!check_collision(Rotation, tetros)) {
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
                if (!check_collision(Rotation, tetros)) {
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
                if (!check_collision(Rotation, tetros)) {
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
                if (!check_collision(Rotation, tetros)) {
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
