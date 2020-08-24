#include "AdjustBar.h"
using namespace sf;


AdjustBar::AdjustBar(short int _value , FloatRect _rect):value(_value),rect(_rect)
{
    rect.left+=rect.width+50;
    rect.width=200;
}
void AdjustBar::setValue_mouse()
{
    Vector2i mousePosition = Mouse::getPosition();
    if (mousePosition.x < rect.left) {
        value = 0;
    }
    else if (mousePosition.x > rect.left + rect.width) {
        value = 100;
    }
    else {
        value = (mousePosition.x - rect.left) / rect.width * 100;
    }
}
void AdjustBar::draw(RenderTarget &target, RenderStates states) const {
    RectangleShape shape(Vector2f ( 200 ,rect.height ) );
    shape.setPosition( rect.left  , rect.top );
    shape.setFillColor(Color::Transparent);
    shape.setOutlineThickness(2);
    shape.setOutlineColor(Color::Black);
    target.draw(shape);
    shape.setSize(Vector2f (value * 2  ,rect.height ) );
    shape.setFillColor(Color::Red);
    shape.setOutlineThickness(0);
    target.draw(shape);
}
