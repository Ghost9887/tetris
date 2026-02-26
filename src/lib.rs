pub mod game;
pub mod rendering;

use crate::game::cells::Cell;

pub fn run() {
    let cells: Vec<Vec<Cell>> = game::cells::create_board();
    rendering::board::draw_board(&cells);
}
