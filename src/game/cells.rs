use macroquad::color::Color;
use macroquad::color::colors::LIGHTGRAY;
use macroquad::window::screen_width;
use macroquad::window::screen_height;

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
    pub fn getX(&self) -> f32 {
        self.x
    }
    pub fn getY(&self) -> f32 {
        self.y
    }
    pub fn getSize(&self) -> f32 {
        self.size
    }
    pub fn getColour(&self) -> Color {
        self.colour
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
            row.push(Cell::new(x as f32 * cell_size + x_padding, y as f32 * cell_size + y_padding, cell_size));
        }
        board.push(row);
    } 

    board
}
