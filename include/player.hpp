#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "common.hpp"
#include "tetro.hpp"

class Player {
public:
    Player(Tetro tetro);
    ~Player() = default;
    void set_current_tetro(Tetro tetro);
    Tetro &get_current_tetro();
private:
    Tetro current_tetro;
};

#endif
