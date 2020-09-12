#include "DotZero.h"
#include "ManagerManager.h"
using namespace sf;

DotZero::DotZero(RenderWindow& window_ref, ManagerManager& manager_ref) : Screen(window_ref,manager_ref,"fonts\\Roboto-Light.ttf",50)
{

    text = Text("DotZero",Screen::getFont(),getNormalFontSize());
    for(int i=0;i<3;i++){
        glitch[i] = Text("DotZero",Screen::getFont(),getNormalFontSize());
        FloatRect textRect = glitch[i].getLocalBounds();
        glitch[i].setOrigin(textRect.left + textRect.width/2.0f,
                        textRect.top  + textRect.height/2.0f);
    }
    glitch[0].setColor(Color::Red);
    glitch[1].setColor(Color::Green);
    glitch[2].setColor(Color::Blue);


    FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f,
                textRect.top  + textRect.height/2.0f);
    text.setPosition(Vector2f(window_ref.getSize().x/2.0f,window_ref.getSize().y/2.0f));


}

void DotZero::manageInput(Keyboard::Key key){
    if(key==Keyboard::Escape || key==Keyboard::Enter || key==Keyboard::Space){
        getManager_ref().setState();
    }
}

void DotZero::manageInput(Mouse::Button button, bool released)
{
    if (button == Mouse::Left || button == Mouse::Right) {
        getManager_ref().setState();
    }
}

void DotZero::update(){
    if(shown)
        alpha-=2;
    else
        alpha+=2;
    if(alpha<0)
        alpha=0;
    if(alpha>=254){
        if(!full){
            timer.restart();
            full=true;
        }
        alpha=255;
        if(timer.getElapsedTime().asMilliseconds()>=700)
            shown=true;

    }
    if(shown && alpha <= 0)
        getManager_ref().setState();
    text.setFillColor(Color(230,230,230,alpha));
    if(alpha>=150)
        if(!(rand() % 12 ))
            text.setPosition(Vector2f(getWindow_ref().getSize().x/2.0f + ((rand()%10)-5) ,getWindow_ref().getSize().y/2.0f + ((rand()%6)-3)));
    else
        text.setPosition(Vector2f(getWindow_ref().getSize().x/2.0f ,getWindow_ref().getSize().y/2.0f ));


    for(int i=0;i<3;i++){
        Color c=glitch[i].getColor();
        if(alpha>=100){
            if(rand()%2)
                glitch[i].setPosition(Vector2f(getWindow_ref().getSize().x/2.0f + ((rand()%20)-10) ,getWindow_ref().getSize().y/2.0f + ((rand()%10)-5)));
            if(rand()%2)
                glitch[i].setCharacterSize(getNormalFontSize());
            else
                glitch[i].setCharacterSize(getNormalFontSize()+4);
            c.a=alpha-100;
        }
        else
            c.a=0;
        glitch[i].setColor(c);
    }

    draw();
}

void DotZero::updateMouse()
{

}

void DotZero::drawSelected()
{

}

void DotZero::draw(){
    getWindow_ref().clear(Color(15,15,15,200));
    for(int i=0;i<3;i++)
        getWindow_ref().draw(glitch[i]);
    getWindow_ref().draw(text);
}
