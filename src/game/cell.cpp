#include "cell.hpp"

Cell create_cell(int x, int y) {
    Cell cell;
    cell.rect = { x, y, CELL_SIZE, CELL_SIZE };
    cell.active = false;
    cell.colour = { 0, 0, 0, 255 };
    return cell;
}
