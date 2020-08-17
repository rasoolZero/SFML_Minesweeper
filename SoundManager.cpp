#include "SoundManager.h"
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
    sounds[5].setLoop(true);
    sounds[6].setLoop(true);
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

void SoundManager::changeVolumeSoundEffects(float delta){
    for(int i=0;i<5;i++){
        sounds[i].setVolume(sounds[i].getVolume()+delta);
        if(sounds[i].getVolume()>100)
            sounds[i].setVolume(100);
    }
}
void SoundManager::changeVolumeMusics(float delta){
    for(int i=5;i<sounds.size();i++){
        sounds[i].setVolume(sounds[i].getVolume()+delta);
        if(sounds[i].getVolume()>100)
            sounds[i].setVolume(100);
    }
}
void SoundManager::setVolumeSoundEffects(float value){
    for(int i=0;i<5;i++){
        sounds[i].setVolume(value);
        if(sounds[i].getVolume()>100)
            sounds[i].setVolume(100);
    }
}
void SoundManager::setVolumeMusics(float value){
    for(int i=5;i<sounds.size();i++){
        sounds[i].setVolume(value);
        if(sounds[i].getVolume()>100)
            sounds[i].setVolume(100);
    }
}

float SoundManager::getSoundEffectVolume(){
    return sounds[0].getVolume();
}
float SoundManager::getMusicVolume(){
    return sounds[sounds.size()-1].getVolume();
}
bool SoundManager::isPlaying(Sounds sound){
    return sounds[static_cast<int>(sound)].getStatus()==Sound::Playing;
}
