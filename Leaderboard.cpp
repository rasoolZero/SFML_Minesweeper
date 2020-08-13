#include "Leaderboard.h"
#include <iostream>
#include <fstream>
using namespace std;
using namespace sf;

Leaderboard::Leaderboard()
{

    ifstream f(fileName);
    if(!f.good())
        init();
    else
        load();

}
void Leaderboard::init(){
    Record sample={"",seconds(0)};
    for(int j=0;j<3;j++)
        for(int i=0;i<10;i++){
            highScores[j][i]=sample;
        }
    save();
}
void Leaderboard::load(){
    ifstream f;
    f.open(fileName,ios::binary | ios::in);
    f.read( (char *)&highScores ,30*sizeof(Record));
    f.close();
}

void Leaderboard::save(){
    ofstream f;
    f.open(fileName,ios::binary | ios::out);
    f.write( (char *)&highScores ,30*sizeof(Record));
    f.close();
}
