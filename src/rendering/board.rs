use macroquad::prelude::*;
use crate::game::cells::Cell;

pub fn draw_board(board: &Vec<Vec<Cell>>) {
    for row in board {
        for cell in row {
            draw_rectangle_lines(
                cell.getX(),
                cell.getY(),
                cell.getSize(),
                cell.getSize(),
                2.0,
                cell.getColour()
            );
        }
    }
}
