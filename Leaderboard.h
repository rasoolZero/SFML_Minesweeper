#ifndef LEADERBOARD_H
#define LEADERBOARD_H
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

typedef struct Record{
    char name[16];
    Time score;
}Record;

class Leaderboard
{
    public:
        Leaderboard();
        enum Difficulties{Easy,Normal,Hard};
        bool isHighscore(Time time,Difficulties difficulty);
        void addScore(Time time,char name[16],Difficulties difficulty);


    protected:

    private:
        Record highScores[3][10];
        string fileName="scores.dat";

        void init();
        void load();
        void save();

};

#endif // LEADERBOARD_H
