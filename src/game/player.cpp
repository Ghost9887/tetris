#include "player.hpp"

Player::Player(Tetro tetro) : current_tetro(tetro), next_tetros(), reserve_tetro(std::nullopt), reserved(false) 
{
    for (int i = 0; i < AMOUNT_OF_NEXT_TETROS; i++) {
        next_tetros.push(Tetro::create_random_tetro());
    }
}

Tetro &Player::get_current_tetro() {
    return current_tetro;
}

void Player::get_next_tetro() {
    current_tetro = next_tetros.front();
    next_tetros.pop();
    next_tetros.push(Tetro::create_random_tetro());
    reserved = false;
}

std::queue<Tetro> &Player::get_next_tetros() {
    return next_tetros;
}

void Player::reserve_current_tetro() {
    if (!reserved) {
        if (!reserve_tetro.has_value()) {
            reserve_tetro = current_tetro;
            get_next_tetro();
        } else {
            std::swap(current_tetro, reserve_tetro.value());
        }

        reserve_tetro->set_row(0);
        reserve_tetro->set_column(COLUMNS / 2);

        reserved = true;
    }
}

