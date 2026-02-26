use macroquad::prelude::*;

use tetris::game::cells::Cell;
use tetris::game::tetros::Tetro;
use tetris::game::cells::create_board;

#[macroquad::main("Tetris")]
async fn main() {

    let mut cells: Vec<Vec<Cell>> = create_board();
    let mut tetros: Vec<Tetro> = vec![];
    //Temp
    tetros.push(Tetro::new(4, 0, 'T'));

    loop {
        tetris::run(&mut cells, &mut tetros);
        next_frame().await
    }
}
