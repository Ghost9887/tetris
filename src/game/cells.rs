use macroquad::color::Color;
use macroquad::color::colors::LIGHTGRAY;
use macroquad::window::screen_width;
use macroquad::window::screen_height;
use crate::Tetro;

pub struct Cell {
    x: f32,
    y: f32,
    size: f32,
    colour: Color,
    active: bool,
}
impl Cell {
    pub fn new(x: f32, y: f32, size: f32) -> Self {
        Cell {
            x,
            y,
            size,
            colour: LIGHTGRAY,
            active: false,
        }
    }
    pub fn get_x(&self) -> f32 {
        self.x
    }
    pub fn get_y(&self) -> f32 {
        self.y
    }
    pub fn get_size(&self) -> f32 {
        self.size
    }
    pub fn get_colour(&self) -> Color {
        self.colour
    }
    pub fn set_active(&mut self, new_active: bool) {
        self.active = new_active;
    }
    pub fn set_colour(&mut self, new_colour: Color) {
        self.colour = new_colour;
    }
    pub fn is_active(&self) -> bool {
        self.active
    }
    fn reset(&mut self) {
        self.active = false;
        self.colour = LIGHTGRAY;
    }
}

pub fn create_board() -> Vec<Vec<Cell>> {
    let mut board: Vec<Vec<Cell>> = vec![];
   
    let cell_size: f32 = 30.0;

    let x_padding: f32 = (screen_width() / 2.0) - ((cell_size * 10.0) / 2.0);
    let y_padding: f32 = (screen_height() / 2.0) - ((cell_size * 20.0) / 2.0);

    for y in 0..20 {
        let mut row: Vec<Cell> = vec![];
        for x in 0..10 {
            row.push(
                Cell::new(
                    x as f32 * cell_size + x_padding, 
                    y as f32 * cell_size + y_padding, 
                    cell_size
                )
            );
        }
        board.push(row);
    } 

    board
}

fn reset_board(board: &mut Vec<Vec<Cell>>) {
    for row in board {
        for cell in row {
            cell.reset();
        }
    }
}

pub fn update_board(board: &mut Vec<Vec<Cell>>, tetros: &Vec<Tetro>) {
    reset_board(board);

    for y in 0..20 {
        for x in 0..10 {
            for tetro in tetros {
                if tetro.get_x() == x && tetro.get_y() == y {
                    board[y as usize][x as usize].set_colour(tetro.get_colour());
                    board[y as usize][x as usize].set_active(true);
                }
            }
        }
    }
}
