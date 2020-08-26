#ifndef CELL_H
#define CELL_H
#include <SFML/Graphics.hpp>
#include "SpriteSheet.h"
using namespace sf;


class Cell : public Drawable
{

    public:
        Cell(int i,int j,float size,Vector2f _offset,int seed,int value=0);
        enum CellState{Hidden,Revealed,Flagged};
        void setValue(int value){this->value=value;}
        int getValue(){return value;}
        void setState(CellState state){this->state=state;}
        CellState getState(){return state;}
        void reveal();
        bool flag();
        void update();
        virtual void draw(RenderTarget & target,RenderStates states) const;

    protected:

    private:
        int value;
        Vector2i index;
        CellState state;
        static Texture cellBackground;
        static Texture revealedT;
        RectangleShape shape;
        RectangleShape background;
        static std::vector<Texture> numbers;
        static bool loaded;
        SpriteSheet sprites;

};
#endif // CELL_H
