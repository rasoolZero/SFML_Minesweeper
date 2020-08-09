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
        square.setPosition(getPosition());
        Texture* texture=new Texture();
        if(!texture->loadFromFile("images/cell.png"))
            throw std::runtime_error("could not load cell background image");
        square.setTexture(texture);
        target.draw(square);
        delete texture;
    }


    if(state==CellState::Flagged){
        RectangleShape square(getScale());
        square.setPosition(getPosition());
        Texture* texture=new Texture();
        if(!texture->loadFromFile("images/flag.png"))
            throw std::runtime_error("could not load flag image");
        square.setTexture(texture);
        target.draw(square);
        delete texture;
    }
    if(state==CellState::Revealed){
        if(value==-1){
            RectangleShape square(getScale());
            square.setPosition(getPosition());
            Texture* texture=new Texture();
            if(!texture->loadFromFile("images/bomb.png"))
                throw std::runtime_error("could not load bomb image");
            square.setTexture(texture);
            target.draw(square);
            delete texture;
        }
        if(value>0){
            RectangleShape square(getScale());
            square.setPosition(getPosition());
            Texture* texture=new Texture();
            if(!texture->loadFromFile("images/"+std::to_string(value)+".png"))
                throw std::runtime_error("could not load a cell number image");
            square.setTexture(texture);
            target.draw(square);
            delete texture;
        }
    }
}
