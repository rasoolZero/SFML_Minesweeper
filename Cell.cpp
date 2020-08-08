#include "Cell.h"
#include<string>
#include <SFML/Graphics.hpp>
using namespace sf;

Cell::Cell(int i,int j,float size)
{

    this->value=0;
    this->state=CellState::Hidden;
    index.x=i;
    index.y=j;
    setPosition(i*size,j*size);
    setScale(size,size);
}

void Cell::reveal(){
    if(state!=CellState::Flagged){
        state=CellState::Revealed;
        if(value==0){
            //reveal neighbor cells
        }
        if(value==-1){
            //game over!
        }
    }
}
void Cell::flag(){
    if(state==CellState::Hidden)
        state=CellState::Flagged;
    else if(state == CellState::Flagged)
        state=CellState::Hidden;
}


void Cell::draw(RenderTarget& target, RenderStates states) const{
    //drawing background
    {
        RectangleShape square(getScale());
        square.setOrigin(getPosition());
        Texture* background=new Texture();
        background->loadFromFile("images/cell.png");
        square.setTexture(background);
        target.draw(square);
        delete background;
    }


    if(state==CellState::Flagged){
        RectangleShape square(getScale());
        square.setOrigin(getPosition());
        Texture* background=new Texture();
        background->loadFromFile("images/flag.png");
        square.setTexture(background);
        target.draw(square);
        delete background;
    }
    if(state==CellState::Revealed){
        if(value==-1){
            RectangleShape square(getScale());
            square.setOrigin(getPosition());
            Texture* background=new Texture();
            background->loadFromFile("images/bomb.png");
            square.setTexture(background);
            target.draw(square);
            delete background;
        }
        if(value>0){
            RectangleShape square(getScale());
            square.setOrigin(getPosition());
            Texture* background=new Texture();
            background->loadFromFile("images/"+std::to_string(value)+".png");
            square.setTexture(background);
            target.draw(square);
            delete background;
        }
    }
}
