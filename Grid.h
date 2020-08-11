#ifndef GRID_H
#define GRID_H
#include "Cell.h"
#include <vector>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

class Grid
{
    public:
        Grid(RenderWindow & w_ref,int width,int height,int bombNumber=10);
        void update();

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
};

#endif // GRID_H
