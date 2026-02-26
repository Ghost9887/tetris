use macroquad::prelude::*;
use crate::game::cells::Cell;

pub fn draw_board(board: &Vec<Vec<Cell>>) {
    for row in board {
        for cell in row {
            if cell.is_active() {
                draw_rectangle(
                    cell.get_x(),
                    cell.get_y(),
                    cell.get_size(),
                    cell.get_size(),
                    cell.get_colour()
                );
            }else {
                draw_rectangle_lines(
                    cell.get_x(),
                    cell.get_y(),
                    cell.get_size(),
                    cell.get_size(),
                    2.0,
                    cell.get_colour()
                );
            }
        }
    }
}
