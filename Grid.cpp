#include "Grid.h"
#include <random>
#include <iostream>
using namespace std;
using namespace sf;

Grid::Grid(RenderWindow & w_ref,int width,int height,int bombNumber) : window_ref(w_ref)
{
    topMargin=48;
    maxSize = w_ref.getSize().x/(float)width < (w_ref.getSize().y-topMargin)/(float)(height) ? w_ref.getSize().x/(float)width : (w_ref.getSize().y-topMargin)/(float)(height) ;
    topLeftCorner.x=(w_ref.getSize().x-maxSize*width)/2;
    topLeftCorner.y=(w_ref.getSize().y-topMargin-maxSize*height)/2 + topMargin;
    this->width=width;
    this->height=height;
    cells = vector<Cell>();


    // bomb based on a fixed amount of bombs and a random index;
    for(int i=0;i<width;i++)
        for(int j=0;j<height;j++)
            cells.push_back(Cell(i,j,maxSize,topLeftCorner));

    int bombsPlaced=0;
    while(bombsPlaced!=bombNumber){
        int index=indexConverter({rand()%width,rand()%height});
        if( !cells[index].getValue() ){
            cells[index].setValue(-1);
            bombsPlaced++;
        }
    }
}

void Grid::update(){
    window_ref.clear(Color(200,200,200));
    checkInput();
    drawTop();
    draw();
}

void Grid::draw(){
    for(auto cell : cells){
        cell.draw(window_ref,RenderStates());
    }
}
void Grid::drawTop(){
    RectangleShape shape({window_ref.getSize().x,topMargin});
    shape.setFillColor(Color(150,150,150));
    window_ref.draw(shape);
}

void Grid::checkInput(){
    static bool prevRightButtonStatus = false;
    static bool prevLeftButtonStatus = false;

    if(Mouse::isButtonPressed(Mouse::Right) && !prevRightButtonStatus){
        //flag cells
        Vector2i pos=mousePos();
        if(isMouseOnGrid(pos)){
            Vector2i index2D=mousePosToIndex(pos);
            int index = indexConverter(index2D);
            cells[index].flag();
        }
    }
    else if(Mouse::isButtonPressed(Mouse::Left) && !prevLeftButtonStatus){
        //revealing cells;
        Vector2i pos=mousePos();
        if(isMouseOnGrid(pos)){
            Vector2i index2D=mousePosToIndex(pos);
            cells[indexConverter(index2D)].reveal();
        }
    }


    prevRightButtonStatus=Mouse::isButtonPressed(Mouse::Right);
    prevLeftButtonStatus=Mouse::isButtonPressed(Mouse::Left);
}
Vector2i Grid::mousePos(){
    return Mouse::getPosition(window_ref);
}

bool Grid::isMouseOnGrid(Vector2i & pos){
    if(pos.x>=topLeftCorner.x && pos.x<=topLeftCorner.x + width*maxSize)
        if(pos.y>=topLeftCorner.y && pos.y<=topLeftCorner.y + height*maxSize)
            return true;
    return false;
}
Vector2i Grid::mousePosToIndex(Vector2i & pos){
    Vector2i result;
    Vector2i posOnGrid=pos-static_cast<Vector2i>(topLeftCorner);
    result.x=posOnGrid.x/maxSize;
    result.y=posOnGrid.y/maxSize;
    return result;
}
int Grid::indexConverter(Vector2i index){
    return height*index.x+index.y;
}
