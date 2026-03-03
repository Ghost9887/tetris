#include "tetro.hpp"

Tetro::Tetro(char id) :
    column(COLUMNS / 2), row(0), id(id), shape(), colour(), fixed(false) 
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
    for (int x = 0; x < tetros.size(); x++) {
        SDL_SetRenderDrawColor(rnd, tetros.at(x).colour.r, tetros.at(x).colour.g, tetros.at(x).colour.b, tetros.at(x).colour.a);
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (tetros.at(x).shape[i][j] == 1) {
                    SDL_RenderFillRect(rnd, &cells.at(tetros.at(x).row + i).at(tetros.at(x).column + j).rect);
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

bool Tetro::not_out_of_bounds(Direction dir, Tetro &tetro, const std::vector<Tetro> &tetros) {
    int next_row = tetro.row;
    int next_column = tetro.column;
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
    
    //bounds
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (tetro.shape[i][j] == 1) {
                int next_row_sub = next_row + i;
                int next_column_sub = next_column + j;
                if (next_row_sub >= ROWS || next_column_sub < 0 || next_column_sub >= COLUMNS ) {
                    if (dir == Down) {
                        tetro.set_fixed(true);
                    }
                    return false;
                }
            }
        }
    }

    //other tetros
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (tetro.shape[i][j] == 1) {
                int current_next_row = next_row + i;
                int current_next_column = next_column + j;
                for (int t = 0; t < tetros.size() - 1; t++) {
                    for (int k = 0; k < 4; k++) {
                        for (int l = 0; l < 4; l++) {
                            if (tetros.at(t).shape[k][l] == 1) {
                                int tetro_row = tetros.at(t).row + k;
                                int tetro_column = tetros.at(t).column + l;
                                if (current_next_row == tetro_row && current_next_column == tetro_column) {
                                    if (dir == Down) {
                                        tetro.set_fixed(true);
                                    }
                                    return false;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return true;
}

void Tetro::move(Tetro &tetro, Direction dir, const std::vector<Tetro> &tetros) {
    switch (dir) {
        case Down:
            if (tetro.not_out_of_bounds(Down, tetro, tetros)) tetro.row++;
            break;
        case Right:
            if (tetro.not_out_of_bounds(Right, tetro, tetros)) tetro.column++;
            break;
        case Left:
            if (tetro.not_out_of_bounds(Left, tetro, tetros)) tetro.column--;
            break;
        default: break;
    }
}

void Tetro::set_fixed(bool value) {
    fixed = value;
}

bool Tetro::is_fixed() {
    return fixed;
}
