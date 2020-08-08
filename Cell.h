#ifndef CELL_H
#define CELL_H
#include <SFML/Graphics.hpp>
using namespace sf;


class Cell : public Drawable, public Transformable
{
    enum CellState{Hidden,Revealed,Flagged};

    public:
        Cell(int i,int j,float size);
        void setValue(int value){this->value=value;}
        int getValue(){return value;}
        void setState(CellState state){this->state=state;}
        CellState getState(){return state;}
        virtual void draw(RenderTarget& target, RenderStates states) const;
        void reveal();
        void flag();

    protected:

    private:
        int value;
        Vector2i index;
        CellState state;

};

#endif // CELL_H
