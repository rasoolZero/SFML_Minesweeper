#ifndef BACKGROUND_H
#define BACKGROUND_H
#include <SFML/Graphics.hpp>
#include "SpriteSheet.h"
using namespace sf;

class Background : public Drawable
{
    public:
        Background(RenderWindow & window_ref);
        virtual void draw(RenderTarget& target,RenderStates states=RenderStates::Default) const;
        void update();

    protected:

    private:
        RectangleShape shapes[5];
        bool isFlag[5];
        Texture bombT;
        SpriteSheet sprites[5];
};

#endif // BACKGROUND_H
