#include "Leaderboard.h"
#include <iostream>
#include <fstream>
#include <cstring>
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
    for(int j=0;j<3;j++)
        for(int i=0;i<10;i++){
            Record sample={"aaaaaaaaaaaaaaa",seconds(i)};
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

bool Leaderboard::isHighscore(Time time,Difficulties difficulty){
    for(int i=0;i<10;i++){
        if( time<highScores[(int)difficulty][i].score || highScores[(int)difficulty][i].score.asSeconds()==0.0 ){
            return true;
        }
    }
    return false;
}
void Leaderboard::addScore(Time time,char name[16],Difficulties difficulty){
    int diffIndex=(int)difficulty;

    for(int i=0;i<10;i++){
        if( time<highScores[(int)difficulty][i].score || highScores[(int)difficulty][i].score.asSeconds()==0.0 ){
            for(int j=8;j>=i;j--){
                highScores[diffIndex][j+1]=highScores[diffIndex][j];
            }
            Record newScore={"",time};
            strcpy(newScore.name,name);
            highScores[diffIndex][i]=newScore;
        }
    }
}
