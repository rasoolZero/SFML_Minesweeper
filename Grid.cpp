#include "Grid.h"
using namespace std;
using namespace sf;

Grid::Grid(RenderWindow & w_ref,int width,int height) : window_ref(w_ref)
{
    this->width=width;
    this->height=height;
    cells = vector<Cell>();
    for(int i=0;i<width;i++)
        for(int j=0;j<height;j++)
            cells.push_back(Cell(i,j,50));

}

void Grid::update(){
    draw();
}

void Grid::draw(){
    for(auto cell : cells){
        cell.draw(window_ref,RenderStates());
    }
}
