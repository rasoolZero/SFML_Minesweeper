#include "Grid.h"
#include "GameManager.h"
#include <ctime>
#include <random>
using namespace std;
using namespace sf;

Grid::Grid(RenderWindow & w_ref,SoundManager & _soundManager,GameManager & _gameManager_ref,int width,int height,int bombNumber)
: window_ref(w_ref) , soundManager(_soundManager),gameManager_ref(_gameManager_ref)
{
    bombs=bombNumber;
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
        int index=indexConverter(rand()%width,rand()%height);
        if( !cells[index].getValue() ){
            cells[index].setValue(-1);
            bombsPlaced++;
        }
    }
}

Grid::Grid(RenderWindow& window_ref, SoundManager& soundManager,GameManager & _gameManager_ref)
    :window_ref(window_ref)
    ,soundManager(soundManager)
    ,gameManager_ref(_gameManager_ref)
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
    bombs=bombNumber;
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
        int index = indexConverter( rand() % width,rand() % height );
        if (!cells[index].getValue()) {
            cells[index].setValue(-1);
            bombsPlaced++;
        }
    }
}

void Grid::draw(){
    for(auto cell : cells){
        cell.update();
        window_ref.draw(cell);
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
    static bool prevMiddleButtonStatus = false;

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
                gameManager_ref.startTimer();
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
    else if(Mouse::isButtonPressed(Mouse::Middle) && !prevMiddleButtonStatus){

        Vector2i pos=mousePos();
        if(isMouseOnGrid(pos)){
            Vector2i index2D=mousePosToIndex(pos);
            if(middleClickCheck(index2D)){
                soundManager.play(SoundManager::Reveal);
                revealMiddleClick(index2D);
            }
            checkGame();
        }
    }


    prevRightButtonStatus=Mouse::isButtonPressed(Mouse::Right);
    prevLeftButtonStatus=Mouse::isButtonPressed(Mouse::Left);
    prevMiddleButtonStatus=Mouse::isButtonPressed(Mouse::Middle);
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
            int index=indexConverter(i,j);
            if(cells[index].getValue()==-1)
                continue;

            int neighborBombs=0;
            for(int x=j-1;x<=j+1;x++){
                for(int k=i-1;k<=i+1;k++){
                    if( !(k==i && x==j) && x>=0 && x < height && k>=0 && k < width){
                        int index2=indexConverter(k,x);
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
int Grid::indexConverter(int x,int y){
    return width*y+x;
}
void Grid::firstClickCheck(int index){
    if(cells[index].getValue()==-1){
        for(int i=0;i<width*height;i++){
            if(cells[i].getValue()!=-1){
                cells[i].setValue(-1);
                cells[index].setValue(0);
                break;
            }
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
                int index=indexConverter(k,x);
                if(cells[index].getState() == Cell::CellState::Hidden || cells[index].getState() == Cell::CellState::Flagged){
                    cells[index].setState(Cell::Hidden);
                    cells[index].reveal();
                    if(cells[index].getValue()==0){
                        revealNeighbors({k,x});
                    }
                }
            }
        }
    }
}
void Grid::revealMiddleClick(Vector2i pos){
    int j=pos.y;
    int i=pos.x;
    bool bomb=false;
    for(int x=j-1;x<=j+1;x++){
        for(int k=i-1;k<=i+1;k++){
            if( !(k==i && x==j) && x>=0 && x < height && k>=0 && k < width){
                int index=indexConverter(k,x);
                if(cells[index].getValue()==-1 && cells[index].getState() == Cell::Hidden ){
                    bomb=true;
                }
                if(cells[index].getState() == Cell::CellState::Hidden && cells[index].getValue() != -1){
                    cells[index].setState(Cell::Hidden);
                    cells[index].reveal();
                    if(cells[index].getValue()==0){
                        revealNeighbors({k,x});
                    }
                }
            }
        }
    }
    if(bomb)
        gameover();
}
bool Grid::middleClickCheck(Vector2i pos){
    int indexCell=indexConverter(pos);
    if(cells[indexCell].getState() != Cell::Revealed || cells[indexCell].getValue() == 0)
        return false;
    int j=pos.y;
    int i=pos.x;
    int bombs=cells[indexCell].getValue();
    for(int x=j-1;x<=j+1;x++){
        for(int k=i-1;k<=i+1;k++){
            if( !(k==i && x==j) && x>=0 && x < height && k>=0 && k < width){
                int index=indexConverter(k,x);
                if(cells[index].getState() == Cell::CellState::Flagged){
                    bombs--;
                }
            }
        }
    }
    if(!bombs)
        return true;
    return false;
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
        gameManager_ref.stopTimer();
        //you won =D
    }
}
void Grid::gameover(){
    //you lost =(
    gameManager_ref.stopTimer();
    state=GridState::Lost;
    soundManager.play(SoundManager::Explosion);
    for(int i=0;i<cells.size();i++){
        if(cells[i].getValue()==-1){
            cells[i].setState(Cell::Revealed);
        }
    }
}
int Grid::getBombCount(){
    return bombs;
}
int Grid::getFlagCount(){
    int result=0;
    for(Cell cell : cells){
        if(cell.getState()==Cell::Flagged)
            result++;
    }
    return result;
}
