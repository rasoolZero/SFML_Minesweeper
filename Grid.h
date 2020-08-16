#ifndef GRID_H
#define GRID_H
#include "Cell.h"
#include "SoundManager.h"
#include <vector>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

class Grid
{
    public:
        Grid(RenderWindow & w_ref,SoundManager & _soundManager ,int width,int height,int bombNumber=10);
        Grid(RenderWindow& window_ref, SoundManager& soundManager);
        enum GridState{Playing, Won, Lost};
        void setState(GridState _state){state=_state;}
        GridState getState(){return state;}
        void update();
        void setupGrid(int width, int height, int bombNumber = 10);
    protected:

    private:
        vector<Cell> cells;
        RenderWindow & window_ref;
        int width;
        int height;
        int topMargin;
        float maxSize;
        Vector2f topLeftCorner;
        void draw();
        void drawTop();
        void checkInput();
        Vector2i mousePos();
        bool isMouseOnGrid(Vector2i & pos);
        Vector2i mousePosToIndex(Vector2i & pos);
        int indexConverter(Vector2i index);
        bool firstClick;
        void calculateValue();
        void firstClickCheck(int index);
        void revealNeighbors(Vector2i pos);
        void checkGame();
        void gameover();
        GridState state;
        SoundManager & soundManager;
};

#endif // GRID_H
