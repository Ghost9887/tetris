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
    std::optional<Tetro> &get_reserved_tetro();
    int get_score();
    void add_score(int value);
private:
    Tetro current_tetro;
    std::queue<Tetro> next_tetros;
    std::optional<Tetro> reserved_tetro;
    bool reserved;
    int score;
};

#endif
