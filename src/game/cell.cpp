#include "cell.hpp"

Cell create_cell(int x, int y) {
    Cell cell;
    cell.rect = { x, y, CELL_SIZE, CELL_SIZE };
    return cell;
}
