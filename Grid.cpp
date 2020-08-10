#include "Grid.h"
using namespace std;
using namespace sf;

Grid::Grid(RenderWindow & w_ref,int width,int height) : window_ref(w_ref)
{
    topLeftCorner={0,36};
    int topMargin=topLeftCorner.y;
    float maxSize = w_ref.getSize().x/(float)width < (w_ref.getSize().y-topMargin)/(float)(height) ? w_ref.getSize().x/(float)width : (w_ref.getSize().y-topMargin)/(float)(height) ;
    topLeftCorner.x=(w_ref.getSize().x-maxSize*width)/2;
    this->width=width;
    this->height=height;
    cells = vector<Cell>();
    for(int i=0;i<width;i++)
        for(int j=0;j<height;j++)
            cells.push_back(Cell(i,j,maxSize,topLeftCorner));
}

void Grid::update(){
    window_ref.clear(Color(200,200,200));
    drawTop();
    draw();
}

void Grid::draw(){
    for(auto cell : cells){
        cell.draw(window_ref,RenderStates());
    }
}
void Grid::drawTop(){
    RectangleShape shape({window_ref.getSize().x,topLeftCorner.y});
    shape.setFillColor(Color(150,150,150));
    window_ref.draw(shape);
}
