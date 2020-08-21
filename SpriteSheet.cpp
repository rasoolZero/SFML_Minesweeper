#include "SpriteSheet.h"
using namespace sf;
using namespace std;
vector<Texture> SpriteSheet::flags;
vector<Texture> SpriteSheet::bombs;
bool SpriteSheet::loaded=false;

SpriteSheet::SpriteSheet()
{
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
    int index=flagIndex;
    if(flagFramesPassed<=0){
        flagFramesPassed=flagFrames;
        this->flagIndex+=1;
        this->flagIndex%=this->flagCount;
    }
    flagFramesPassed--;
    return &flags[index];
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
