use macroquad::prelude::*;

#[macroquad::main("Tetris")]
async fn main() {
    loop {
        tetris::run();
        next_frame().await
    }
}
