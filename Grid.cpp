#include "Grid.h"
#include <ctime>
#include <random>
using namespace std;
using namespace sf;

Grid::Grid(RenderWindow & w_ref,SoundManager & _soundManager,int width,int height,int bombNumber)
: window_ref(w_ref) , soundManager(_soundManager)
{
    srand(time(nullptr));
    state=GridState::Playing;
    firstClick=true;
    topMargin=48;
    float widthRatio=w_ref.getSize().x/(float)width;
    float heightRatio=(w_ref.getSize().y-topMargin)/(float)(height);
    maxSize = widthRatio < heightRatio ? widthRatio : heightRatio ;
    topLeftCorner.x=(w_ref.getSize().x-maxSize*width)/2;
    topLeftCorner.y=(w_ref.getSize().y-topMargin-maxSize*height)/2 + topMargin;
    this->width=width;
    this->height=height;
    cells = vector<Cell>();


    // bomb based on a fixed amount of bombs and a random index
    for(int j=0;j<height;j++)
        for(int i=0;i<width;i++)
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

Grid::Grid(RenderWindow& window_ref, SoundManager& soundManager)
    :window_ref(window_ref)
    ,soundManager(soundManager)
{
}

void Grid::update(){
    window_ref.clear(Color(200,200,200));
    checkInput();
    drawTop();
    draw();
}

void Grid::setupGrid(int width, int height, int bombNumber)
{
    srand(time(nullptr));
    state = GridState::Playing;
    firstClick = true;
    topMargin = 48;
    float widthRatio = window_ref.getSize().x / (float)width;
    float heightRatio = (window_ref.getSize().y - topMargin) / (float)(height);
    maxSize = widthRatio < heightRatio ? widthRatio : heightRatio;
    topLeftCorner.x = (window_ref.getSize().x - maxSize * width) / 2;
    topLeftCorner.y = (window_ref.getSize().y - topMargin - maxSize * height) / 2 + topMargin;
    this->width = width;
    this->height = height;
    cells = vector<Cell>();


    // bomb based on a fixed amount of bombs and a random index
    for (int j = 0; j < height; j++)
        for (int i = 0; i < width; i++)
            cells.push_back(Cell(i, j, maxSize, topLeftCorner));

    int bombsPlaced = 0;
    while (bombsPlaced != bombNumber) {
        int index = indexConverter({ rand() % width,rand() % height });
        if (!cells[index].getValue()) {
            cells[index].setValue(-1);
            bombsPlaced++;
        }
    }
}

void Grid::draw(){
    for(auto cell : cells){
        cell.draw(window_ref,RenderStates());
    }
}
void Grid::drawTop(){
    RectangleShape shape(Vector2f(window_ref.getSize().x,topMargin));
    shape.setFillColor(Color(150,150,150));
    window_ref.draw(shape);
}

void Grid::checkInput(){
    if(state!=GridState::Playing)
        return;
    static bool prevRightButtonStatus = false;
    static bool prevLeftButtonStatus = false;

    if(Mouse::isButtonPressed(Mouse::Right) && !prevRightButtonStatus){
        //flag cells
        Vector2i pos=mousePos();
        if(isMouseOnGrid(pos)){
            Vector2i index2D=mousePosToIndex(pos);
            int index=indexConverter(index2D);
            if(cells[index].flag()){
                if(cells[index].getState() == Cell::Flagged)
                    soundManager.play(SoundManager::FlagOn);
                else
                    soundManager.play(SoundManager::FlagOff);
            }
        }
    }
    else if(Mouse::isButtonPressed(Mouse::Left) && !prevLeftButtonStatus){
        //revealing cells;
        Vector2i pos=mousePos();
        if(isMouseOnGrid(pos)){
            Vector2i index2D=mousePosToIndex(pos);
            int index=indexConverter(index2D);

            if(firstClick){
                firstClickCheck(index);
                firstClick=false;
            }

            if(cells[index].getState() == Cell::CellState::Hidden){
                cells[index].reveal();
                if(cells[index].getValue()==0){
                    revealNeighbors(index2D);
                }
                if(cells[index].getValue()==-1){
                    gameover();
                }
                else
                    soundManager.play(SoundManager::Reveal);
                checkGame();
            }
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
void Grid::calculateValue(){
    for(int j=0;j<height;j++){
        for(int i=0;i<width;i++){
            int index=indexConverter({i,j});
            if(cells[index].getValue()==-1)
                continue;

            int neighborBombs=0;
            for(int x=j-1;x<=j+1;x++){
                for(int k=i-1;k<=i+1;k++){
                    if( !(k==i && x==j) && x>=0 && x < height && k>=0 && k < width){
                        int index2=indexConverter({k,x});
                        if(cells[index2].getValue()==-1)
                            neighborBombs++;
                    }
                }
            }
            cells[index].setValue(neighborBombs);
        }
    }
}

int Grid::indexConverter(Vector2i index){
    return width*index.y+index.x;
}
void Grid::firstClickCheck(int index){
    if(cells[index].getValue()==-1){
        cells[index].setValue(0);
        if(!cells[0].getValue()){
            cells[0].setValue(-1);
        }
        else{
            cells[width-1].setValue(-1);
        }
    }
    calculateValue();
}

void Grid::revealNeighbors(Vector2i pos){
    int j=pos.y;
    int i=pos.x;
    for(int x=j-1;x<=j+1;x++){
        for(int k=i-1;k<=i+1;k++){
            if( !(k==i && x==j) && x>=0 && x < height && k>=0 && k < width){
                int index=indexConverter({k,x});
                if(cells[index].getState() == Cell::CellState::Hidden){
                    cells[index].reveal();
                    if(cells[index].getValue()==0){
                        revealNeighbors({k,x});
                    }
                }
            }
        }
    }
}
void Grid::checkGame(){
    bool won=true;
    for(auto cell : cells){
        if( cell.getValue() >=0 ){
            if(cell.getState() != Cell::CellState::Revealed){
                won = false;
            }
        }
    }
    if(won){
        state=GridState::Won;
        soundManager.play(SoundManager::Victory);
        //you won =D
    }
}
void Grid::gameover(){
    //you lost =(
    state=GridState::Lost;
    soundManager.play(SoundManager::Explosion);
    for(int i=0;i<cells.size();i++){
        if(cells[i].getValue()==-1){
            cells[i].reveal();
        }
    }
}
