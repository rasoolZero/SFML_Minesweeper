#include "Cell.h"

Cell::Cell(RenderWindow * window_ptr)
{
    this->state=CellState::Hidden;
    setWindow(window_ptr);
}
