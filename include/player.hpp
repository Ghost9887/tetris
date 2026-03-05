#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "common.hpp"
#include "tetro.hpp"

class Player {
public:
    Player(Tetro tetro);
    ~Player() = default;
    Tetro &get_current_tetro();
    void get_next_tetro();
    void reserve_current_tetro();
    std::queue<Tetro> &get_next_tetros();
private:
    Tetro current_tetro;
    std::queue<Tetro> next_tetros;
    std::optional<Tetro> reserve_tetro;
    bool reserved;
};

#endif
