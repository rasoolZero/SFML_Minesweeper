#ifndef ADJUSTBAR_H
#define ADJUSTBAR_H
#include <SFML/Graphics.hpp>
using namespace sf;


class AdjustBar : public Drawable
{

    public:
        AdjustBar(short int _value , FloatRect _rect);
        void setValue (short int _value){value=_value;}
        short int getValue() { return value; }
        void setValue_mouse();
        virtual void draw (RenderTarget &target, RenderStates states) const;
    protected:

    private:
        short int value;
        FloatRect rect;
};

#endif // ADJUSTBAR_H
