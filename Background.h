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
        RectangleShape flag1;
        RectangleShape flag2;
        RectangleShape bomb;
        Texture bombT;
        SpriteSheet sprite1;
        SpriteSheet sprite2;
};

#endif // BACKGROUND_H
