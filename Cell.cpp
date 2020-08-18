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

Cell::Cell(int i,int j,float size,Vector2f _offset,int value)
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
    shape.setPosition(i*size+_offset.x,j*size+_offset.y);
    shape.setSize(Vector2f(size,size));
    revealed.setPosition(i*size+_offset.x,j*size+_offset.y);
    revealed.setSize(Vector2f(size,size));
    background.setPosition(i*size+_offset.x,j*size+_offset.y);
    background.setSize(Vector2f(size,size));
    flagged.setPosition(i*size+_offset.x,j*size+_offset.y);
    flagged.setSize(Vector2f(size,size));
    revealed.setTexture(&revealedT);
    background.setTexture(&cellBackground);
    flagged.setTexture(&flagT);
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

void Cell::update(){
    if(state==CellState::Revealed){
        if(value==-1){
            shape.setTexture(&bombT);
        }
        if(value>0){
            shape.setTexture(&numbers[value-1]);
        }
    }
}

void Cell::draw(RenderTarget & target,RenderStates states) const{
    if(state!=CellState::Revealed)
        target.draw(background);
    if(state==CellState::Flagged)
        target.draw(flagged);
    if(state==CellState::Revealed){
        target.draw(revealed);
        if(value==-1 || value>0)
        target.draw(shape);
    }

}
