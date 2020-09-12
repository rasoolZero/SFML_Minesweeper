#include "Background.h"
using namespace sf;

Background::Background(RenderWindow & window_ref)
{
    int size=200;
    for(int i=0;i<5;i++){
        shapes[i].setSize(Vector2f(size,size));
        int offset=15;
        shapes[i].setOrigin(size/2,size-offset);
        float factor=((rand()%400)+700)/1000.0f;
        shapes[i].scale(factor,factor);
        shapes[i].setFillColor(Color(255,255,255,220));
        shapes[i].setPosition( window_ref.getSize().x - 150*(i+1) + ((rand()%50)-25) , window_ref.getSize().y);
    }

}
void Background::update(){
    for(int i=0;i<5;i++)
        shapes[i].setTexture(sprites[i].getFlagTexture());
}

void Background::draw(RenderTarget& target,RenderStates states) const{
    for(int i=0;i<5;i++)
        target.draw(shapes[i]);
}
