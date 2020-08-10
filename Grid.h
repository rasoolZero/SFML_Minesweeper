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
        Vector2f topLeftCorner;
        void draw();
        void drawTop();
};

#endif // GRID_H
