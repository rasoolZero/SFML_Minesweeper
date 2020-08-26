#include "SpriteSheet.h"
using namespace sf;
using namespace std;
vector<Texture> SpriteSheet::flags;
vector<Texture> SpriteSheet::bombs;
bool SpriteSheet::loaded=false;

SpriteSheet::SpriteSheet(int seed)
{
    this->seed=seed+time(0);
    srand(seed);
    int multiplier = rand()%5+1;
    flagFramesRestart=60*multiplier;
    if(!loaded){
        loaded=true;
        for(int i=0;i<flagCount;i++){
            flags.push_back(Texture());
            if(!flags[i].loadFromFile("images\\sprites\\flag\\"+to_string(i)+".png"))
                throw std::runtime_error("could not load flag sprites");
            flags[i].setSmooth(true);
        }
        for(int i=0;i<bombCount;i++){
            bombs.push_back(Texture());
            if(!bombs[i].loadFromFile("images\\sprites\\bomb\\"+to_string(i)+".png"))
                throw std::runtime_error("could not load bomb sprites");
            bombs[i].setSmooth(true);
        }
    }
}
Texture* SpriteSheet::getFlagTexture(){
    if(flagFramesRestart == 0){
        int index=flagIndex;
        if(flagFramesPassed<=0){
            flagFramesPassed=flagFrames;
            this->flagIndex+=1;
            this->flagIndex%=this->flagCount;
            if(flagIndex==0){
                srand(seed);
                int multiplier = rand()%5+1;
                flagFramesRestart=60*multiplier;
            }
        }
        flagFramesPassed--;
        return &flags[index];
    }
    else{
        flagFramesRestart--;
        return &flags[0];
    }
}

Texture* SpriteSheet::getBombTexture(){
    int index=bombIndex;
    if(bombFramesPassed<=0){
        bombFramesPassed=bombFrames;
        this->bombIndex+=1;
        this->bombIndex%=this->bombCount;
    }
    bombFramesPassed--;
    return &bombs[index];
}
