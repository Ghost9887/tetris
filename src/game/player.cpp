#include "player.hpp"

Player::Player(Tetro tetro) : current_tetro(tetro) {}

void Player::set_current_tetro(Tetro tetro) {
    current_tetro = tetro;
}

Tetro &Player::get_current_tetro() {
    return current_tetro;
}
