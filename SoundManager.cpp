#include "SoundManager.h"
#include <iostream>
using namespace std;
using namespace sf;

SoundManager::SoundManager()
{
    for(int i=0;i<7;i++){
        buffers.push_back(SoundBuffer());
    }
    if(!buffers[0].loadFromFile("sounds/explosion.wav"))
        throw runtime_error("could not load explosion sound effect");
    if(!buffers[1].loadFromFile("sounds/victory.wav"))
        throw runtime_error("could not load victory sound effect");
    if(!buffers[2].loadFromFile("sounds/flag1.wav"))
        throw runtime_error("could not load flag1 sound effect");
    if(!buffers[3].loadFromFile("sounds/flag2.wav"))
        throw runtime_error("could not load flag2 sound effect");
    if(!buffers[4].loadFromFile("sounds/reveal.wav"))
        throw runtime_error("could not load reveal sound effect");
    if(!buffers[5].loadFromFile("sounds/game.wav"))
        throw runtime_error("could not load game music");
    if(!buffers[6].loadFromFile("sounds/menu.wav"))
        throw runtime_error("could not load menu music");

    for(int i=0;i<buffers.size();i++){
        sounds.push_back(Sound(buffers[i]));
    }
}
void SoundManager::play(Sounds sound){
    sounds[(int)sound].play();
}

void SoundManager::stop(Sounds sound){
    sounds[(int)sound].stop();
}

void SoundManager::stopAll(){
    for(int i=0;i<sounds.size();i++){
        sounds[i].stop();
    }
}
