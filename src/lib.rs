pub mod game;
pub mod rendering;

use crate::game::cells::Cell;
use crate::game::tetros::Tetro;

pub fn run(cells: &mut Vec<Vec<Cell>>, tetros: &mut Vec<Tetro>) {
    game::tetros::update_tetros(tetros);
    game::cells::update_board(cells, &tetros);
    rendering::board::draw_board(&cells);
}
