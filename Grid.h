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
        Grid(RenderWindow & w_ref,int width,int height);
        void update();

    protected:

    private:
        vector<Cell> cells;
        RenderWindow & window_ref;
        int width;
        int height;
        int topMargin;
        Vector2f topLeftCorner;
        void draw();
        void drawTop();
        void checkInput();
};

#endif // GRID_H
