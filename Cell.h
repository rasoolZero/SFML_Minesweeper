#ifndef CELL_H
#define CELL_H
#include <SFML/Graphics.hpp>
using namespace sf;

enum CellState{Hidden,Revealed,Flagged};

class Cell : public Drawable, public Transformable
{
    public:
        Cell(RenderWindow * window_ptr);
        void setWindow(RenderWindow * window_ptr){this->window_ptr=window_ptr;}
        void setValue(int value){this->value=value;}
        int getValue(){return value;}
        void setState(CellState state){this->state=state;}
        CellState getState(){return state;}


    protected:

    private:
        RenderWindow *window_ptr;
        int value;
        CellState state;

};

#endif // CELL_H
