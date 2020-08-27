#include "Background.h"
using namespace sf;

Background::Background(RenderWindow & window_ref):sprites{2,4,7,11,20}
{
    if(!bombT.loadFromFile("images\\sprites\\bomb\\0.png"))
        throw std::runtime_error("could not load bomb sprite");
    int size=200;
    srand(time(0));

    int bombCount=rand()%3+1;
    int bombPlaced=0;
    for(int i=0;i<5;i++)
        isFlag[i]=true;
    while(bombPlaced!=bombCount){
        int index=rand()%5;
        if(isFlag[index]){
            bombPlaced++;
            isFlag[index]=false;
        }
    }
    for(int i=0;i<5;i++){
        shapes[i].setSize(Vector2f(size,size));
        int offset;
        if(isFlag[i])
            offset=15;
        else
            offset=25;
        shapes[i].setOrigin(size/2,size-offset);
        float factor=(((rand()%400)+700)/1000.0f);
        shapes[i].scale(factor,factor);
        shapes[i].setPosition( window_ref.getSize().x - 150*(i+1) + ((rand()%60)-30) , window_ref.getSize().y);
        if(!isFlag[i])
            shapes[i].setTexture(&bombT);
    }

}
void Background::update(){
    for(int i=0;i<5;i++)
        if(isFlag[i])
            shapes[i].setTexture(sprites[i].getFlagTexture());
}

void Background::draw(RenderTarget& target,RenderStates states) const{
    for(int i=0;i<5;i++)
        target.draw(shapes[i]);
}
