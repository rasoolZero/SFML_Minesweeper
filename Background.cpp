#include "Background.h"
using namespace sf;

Background::Background(RenderWindow & window_ref):sprite1(1),sprite2(2)
{
    if(!bombT.loadFromFile("images\\sprites\\bomb\\0.png"))
        throw std::runtime_error("could not load bomb sprite");
    int size=200;
    bomb=RectangleShape(Vector2f(200,200));
    flag1=RectangleShape(Vector2f(200,200));
    flag2=RectangleShape(Vector2f(200,200));
    bomb.setPosition( window_ref.getSize().x - size , window_ref.getSize().y - size + 25 );
    flag1.setPosition( window_ref.getSize().x - size*2 , window_ref.getSize().y - size + 18);
    flag2.setPosition( window_ref.getSize().x - size*3 , window_ref.getSize().y - size + 18 );
    bomb.setTexture(&bombT);
}
void Background::update(){
    flag1.setTexture(sprite1.getFlagTexture());
    flag2.setTexture(sprite2.getFlagTexture());
}

void Background::draw(RenderTarget& target,RenderStates states) const{
    target.draw(flag1);
    target.draw(flag2);
    target.draw(bomb);
}
