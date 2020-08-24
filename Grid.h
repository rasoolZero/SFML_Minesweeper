#ifndef GRID_H
#define GRID_H
#include "Cell.h"
#include "SoundManager.h"
#include <vector>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

class GameManager;

class Grid
{
    public:
        Grid(RenderWindow & w_ref,SoundManager & _soundManager,GameManager & _gameManager_ref ,int width,int height,int bombNumber=10);
        Grid(RenderWindow& window_ref, SoundManager& soundManager,GameManager & _gameManager_ref );
        enum GridState{Playing, Won, Lost};
        void setState(GridState _state){state=_state;}
        GridState getState(){return state;}
        void update();
        void setupGrid(int width, int height, int bombNumber = 10);
        int getBombCount();
        int getFlagCount();
        int getWidth(){return width;}
        int getHeight(){return height;}
        void manageInput(Mouse::Button button);
    protected:

    private:
        vector<Cell> cells;
        RenderWindow & window_ref;
        int width;
        int height;
        int topMargin;
        int bombs;
        float maxSize;
        Vector2f topLeftCorner;
        void draw();
        void drawTop();
        Vector2i mousePos();
        bool isMouseOnGrid(Vector2i & pos);
        Vector2i mousePosToIndex(Vector2i & pos);
        int indexConverter(Vector2i index);
        int indexConverter(int x,int y);
        bool firstClick;
        void calculateValue();
        void firstClickCheck(int index);
        void revealNeighbors(Vector2i pos);
        void revealMiddleClick(Vector2i pos);
        void checkGame();
        bool middleClickCheck(Vector2i pos);
        void gameover();
        GridState state;
        SoundManager & soundManager;
        GameManager & gameManager_ref;


};

#endif // GRID_H
