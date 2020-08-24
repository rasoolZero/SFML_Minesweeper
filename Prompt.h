#ifndef PROMPT_H
#define PROMPT_H
#include <SFML/Graphics.hpp>
using namespace sf;

class Prompt : public Drawable
{
    public:
        Prompt(RenderWindow & window_ref,Font & font);
        bool getState(){return promptOption;}
        void setState(bool state);
        void changeOption();
        FloatRect getTextRect(short int index);
    protected:

    private:
    Text promptYes;
    Text promptNo;
    Text promptText;
    RectangleShape promptBox;
    bool promptOption=false;

    virtual void draw(RenderTarget & target, RenderStates states=RenderStates::Default) const;
};

#endif // PROMPT_H
