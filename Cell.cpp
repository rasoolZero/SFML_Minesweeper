#include "Cell.h"
#include<string>
#include <SFML/Graphics.hpp>
using namespace sf;
Texture Cell::bombT;
Texture Cell::cellBackground;
Texture Cell::flagT;
Texture Cell::revealedT;
std::vector<Texture> Cell::numbers;
bool Cell::loaded;

Cell::Cell(int i,int j,float size,Vector2f _offset,int value):offset(_offset)
{
    if(!loaded){
        if(!bombT.loadFromFile("images/bomb.png"))
            throw std::runtime_error("could not load bomb image");
        if(!cellBackground.loadFromFile("images/cell.png"))
            throw std::runtime_error("could not load cell background image");
        if(!flagT.loadFromFile("images/flag.png"))
            throw std::runtime_error("could not load flag image");
        if(!revealedT.loadFromFile("images/revealed.png"))
            throw std::runtime_error("could not load revealed background image");
        for(int i=0;i<8;i++){
            numbers.push_back(Texture());
        }
        for(int i=0;i<8;i++){
            numbers[i]=Texture();
            if(!numbers[i].loadFromFile("images/"+std::to_string(i+1)+".png"))
                throw std::runtime_error("could not load a cell number image");
        }
        loaded=true;
    }

    this->value=value;
    this->state=CellState::Hidden;
    index.x=i;
    index.y=j;
    setPosition(i*size+_offset.x,j*size+_offset.y);
    setScale(size,size);
}

void Cell::reveal(){
    if(state!=CellState::Flagged){
        state=CellState::Revealed;
    }
}
bool Cell::flag(){
    if(state==CellState::Hidden){
        state=CellState::Flagged;
        return true;
    }
    else if(state == CellState::Flagged){
        state=CellState::Hidden;
        return true;
    }
    return false;
}


void Cell::draw(RenderTarget& target, RenderStates states) const{
    //drawing background
    if(state!=CellState::Revealed)
    {
        RectangleShape square(getScale());
        square.setPosition(getPosition());
        square.setTexture(&cellBackground);
        target.draw(square);
    }


    if(state==CellState::Flagged){
        RectangleShape square(getScale());
        square.setPosition(getPosition());
        square.setTexture(&flagT);
        target.draw(square);
    }
    if(state==CellState::Revealed){
        {
            RectangleShape square(getScale());
            square.setPosition(getPosition());
            square.setTexture(&revealedT);
            target.draw(square);
        }
        if(value==-1){
            RectangleShape square(getScale());
            square.setPosition(getPosition());
            square.setTexture(&bombT);
            target.draw(square);
        }
        if(value>0){
            RectangleShape square(getScale());
            square.setPosition(getPosition());
            square.setTexture(&numbers[value-1]);
            target.draw(square);
        }
    }
}
