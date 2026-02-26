use macroquad::color::Color;
use macroquad::color::colors::*;
use macroquad::time::get_frame_time;

pub struct Tetro {
    x: i32,
    y: i32,
    tetro_type: char,
    colour: Color,
    timer: f32,
}
impl Tetro {
    pub fn new(x: i32, y: i32, tetro_type: char) -> Self {
        Tetro {
            x,
            y,
            tetro_type,
            colour: BLUE,
            timer: 0.5,
        }
    }
    pub fn get_x(&self) -> i32 {
        self.x
    }
    pub fn get_y(&self) -> i32 {
        self.y
    }
    pub fn get_colour(&self) -> Color {
        self.colour
    }
    fn move_down(&mut self) {
        self.y += 1;
    }
    fn time_up(&self) -> bool{
        self.timer <= 0.0
    }
    fn reset_timer(&mut self) {
        self.timer = 0.5;
    }
    fn countdown(&mut self) {
        self.timer -= get_frame_time();
    }
}

pub fn update_tetros(tetros: &mut Vec<Tetro>) {
    for tetro in tetros {
        if tetro.time_up() {
            tetro.reset_timer();
            tetro.move_down();
        }else {
            tetro.countdown();
        }
    }
}
