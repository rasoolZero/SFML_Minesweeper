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
        virtual void manageInput(Keyboard::Key key); //from Screen
        virtual void manageInput(Mouse::Button button, bool released = 0); //from Screen
        virtual void update(); //from Screen
        virtual void updateMouse(); //from Screen
    protected:
        virtual void drawSelected(); //from screen
    private:
        int alpha=0;
        bool shown=false;
        Text text;
        void draw();
};

#endif // DOTZERO_H
