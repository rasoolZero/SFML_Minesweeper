#ifndef CELL_H
#define CELL_H
#include <SFML/Graphics.hpp>
using namespace sf;


class Cell : public Drawable, public Transformable
{

    public:
        Cell(int i,int j,float size,Vector2f _offset,int value=0);
        enum CellState{Hidden,Revealed,Flagged};
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
        Vector2f offset;
        CellState state;
        static Texture bombT;
        static Texture cellBackground;
        static Texture flagT;
        static Texture revealedT;
        static std::vector<Texture> numbers;
        static bool loaded;

};

#endif // CELL_H
