#ifndef LEADERBOARD_H
#define LEADERBOARD_H
#include "Screen.h"
#include "SelectBox.h"
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

class ManagerManager;

typedef struct Record{
    char name[16];
    Time score;
}Record;

class Leaderboard : public Screen
{
    public:
        Leaderboard(RenderWindow & _window_ref, ManagerManager& manager_ref);
        enum Difficulties{Easy,Normal,Hard};
        bool isHighscore(Time time,Difficulties difficulty);
        void addScore(Time time,const char name[16],Difficulties difficulty);

        virtual void update(); //from Screen
        virtual void manageInput(Keyboard::Key key); //from Screen
        virtual void manageInput(Mouse::Button button, bool released = 0); //from Screen
        virtual void updateMouse(); //from screen

        void resetScores();

    protected:
        virtual void drawSelected(); //from screen
    private:
        Record highScores[3][10];
        string fileName="scores.dat";

        short int selectedFontSize = 30;
        Font font;
        Text options[4];
        IntRect optionBoxes[4];
        SelectBox selectBoxes[3];

        Difficulties selectedOption = Difficulties::Easy;


        void setSelectedOption(Difficulties selectedOption);
        void setSelectedOption(short int selectedOptionIndex);

        void init();
        void load();
        void save();
        void reset();

        void draw();
        void drawScores();
        void drawOptions();
};

#endif // LEADERBOARD_H
