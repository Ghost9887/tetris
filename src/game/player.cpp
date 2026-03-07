#include "player.hpp"

Player::Player(Tetro tetro) : 
    current_tetro(tetro), 
    next_tetros(), 
    reserved_tetro(std::nullopt), 
    reserved(false), 
    score(0),
    rows_cleared(0),
    level(1)
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

std::optional<Tetro> &Player::get_reserved_tetro() {
    return reserved_tetro;
}

void Player::reserve_current_tetro() {
    if (!reserved) {
        if (!reserved_tetro.has_value()) {
            reserved_tetro = current_tetro;
            get_next_tetro();
        } else {
            std::swap(current_tetro, reserved_tetro.value());
        }

        reserved_tetro->set_row(0);
        reserved_tetro->set_column(COLUMNS / 2);

        reserved = true;
    }
}

int Player::get_score() {
    return score;
}

void Player::add_score(int value) {
    score += value;
}

int Player::get_level() {
    return level;
}

void Player::add_rows(int rows) {
    rows_cleared += rows;
    if (rows_cleared >= 10 * level && level <= 20) {
        rows_cleared = rows_cleared % 10 * level;
        level++;
    }
}
