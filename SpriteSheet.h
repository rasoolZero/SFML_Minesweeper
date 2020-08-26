#ifndef SPRITESHEET_H
#define SPRITESHEET_H
#include <SFML/Graphics.hpp>
#include <vector>
using namespace std;
using namespace sf;

class SpriteSheet
{
    public:
        SpriteSheet(int seed);
        Texture* getFlagTexture();
        Texture* getBombTexture();

    protected:

    private:
        static vector<Texture> flags;
        static vector<Texture> bombs;
        static bool loaded;

        int flagCount=11;
        int bombCount=10;
        int flagIndex=0;
        int bombIndex=0;
        int flagFrames=8;
        int bombFrames=6;
        int flagFramesPassed=flagFrames;
        int bombFramesPassed=bombFrames;

        int flagFramesRestart=0;
        unsigned int seed;
};

#endif // SPRITESHEET_H
