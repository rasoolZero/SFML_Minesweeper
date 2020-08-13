#ifndef LEADERBOARD_H
#define LEADERBOARD_H
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

class ManagerManager;

typedef struct Record{
    char name[16];
    Time score;
}Record;

class Leaderboard
{
    public:
        Leaderboard(RenderWindow & _window_ref, ManagerManager& manager_ref);
        enum Difficulties{Easy,Normal,Hard};
        bool isHighscore(Time time,Difficulties difficulty);
        void addScore(Time time,char name[16],Difficulties difficulty);

        void update();

        void reset();

    protected:

    private:
        Record highScores[3][10];
        string fileName="scores.dat";
        RenderWindow & window_ref;
        ManagerManager& manager_ref;

        short int normalFontSize = 24;
        short int selectedFontSize = 30;
        Font font;
        Text options[3];
        Color selectedTextColor = Color::Red;
        Color normalTextColor = Color::Black;

        Difficulties selectedOption = Difficulties::Easy;


        void setSelectedOption(Difficulties selectedOption);
        void setSelectedOption(short int selectedOptionIndex);

        void init();
        void load();
        void save();

        void checkInput();
        void draw();
        void drawScores();
        void drawOptions();
        void drawBack();

};

#endif // LEADERBOARD_H
