#include "DotZero.h"
#include "ManagerManager.h"
using namespace sf;

DotZero::DotZero(RenderWindow& window_ref, ManagerManager& manager_ref) : Screen(window_ref,manager_ref,"fonts\\Roboto-Light.ttf",50)
{
    text = Text("DotZero",Screen::getFont(),getNormalFontSize());
    text.setStyle(Text::Bold);

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
    if(alpha>=254)
        shown=true;
    if(shown && alpha <= 0)
        getManager_ref().setState();
    text.setFillColor(Color(0,0,0,alpha));
    draw();
}

void DotZero::updateMouse()
{

}

void DotZero::draw(){
    getWindow_ref().draw(text);
}
