#ifndef DOTZERO_H
#define DOTZERO_H
#include <SFML/Graphics.hpp>
#include "Screen.h"
using namespace sf;

class ManagerManager;

class DotZero : public Screen
{
    public:
        DotZero(RenderWindow& window_ref, ManagerManager& manager_ref);
        virtual void manageInput(Keyboard::Key key);
        virtual void update();
    protected:

    private:
        int alpha=0;
        bool shown=false;
        Text text;
        void draw();
};

#endif // DOTZERO_H
