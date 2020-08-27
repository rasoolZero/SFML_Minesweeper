#include "Prompt.h"
using namespace sf;

Prompt::Prompt(RenderWindow & window_ref,Font & font)
{
    promptYes = Text("Yes",font,24);
    promptNo = Text("No",font,24);
    promptText = Text("Are You Sure?",font,24);

    FloatRect textRect = promptYes.getLocalBounds();
    promptYes.setOrigin(promptYes.getOrigin().x,
        textRect.top  + textRect.height/2.0f);

    promptYes.setPosition(Vector2f(window_ref.getSize().x/2.0f + 20,window_ref.getSize().y/2.0f+ 15 ));


    textRect = promptNo.getLocalBounds();
    promptNo.setOrigin(promptNo.getOrigin().x,
        textRect.top  + textRect.height/2.0f);

    promptNo.setPosition(Vector2f(window_ref.getSize().x/2.0f - promptNo.getGlobalBounds().width-20,window_ref.getSize().y/2.0f + 15));


    textRect = promptText.getLocalBounds();
    promptText.setOrigin(textRect.left + textRect.width/2.0f,
        textRect.top  + textRect.height/2.0f);

    promptText.setPosition(Vector2f(window_ref.getSize().x/2.0f , window_ref.getSize().y/2.0f - 25));

    promptText.setColor(Color::Black);


    promptBox.setSize(Vector2f (promptText.getGlobalBounds().width+10, textRect.height + promptNo.getGlobalBounds().height+50));
    promptBox.setFillColor(Color(250,250,250,160));
    promptBox.setOutlineColor(Color::Black);
    promptBox.setOutlineThickness(3);
    promptBox.setPosition(Vector2f ( window_ref.getSize().x/2.0f - promptBox.getSize().x/2.0f , window_ref.getSize().y/2.0f - promptBox.getSize().y/2.0f ) );

    if(promptOption){
        promptYes.setColor(Color::Red);
        promptNo.setColor(Color::Black);
    }
    else{
        promptNo.setColor(Color::Red);
        promptYes.setColor(Color::Black);
    }
}

void Prompt::draw(RenderTarget & target, RenderStates states) const{

    target.draw(promptBox);
    target.draw(promptYes);
    target.draw(promptNo);
    target.draw(promptText);
}
void Prompt::setState(bool state)
{
    this->promptOption = state;
    if (promptOption) {
        promptYes.setColor(Color::Red);
        promptNo.setColor(Color::Black);
    }
    else {
        promptNo.setColor(Color::Red);
        promptYes.setColor(Color::Black);
    }
}
void Prompt::changeOption(){
    promptOption=!promptOption;
    if(promptOption){
        promptYes.setColor(Color::Red);
        promptNo.setColor(Color::Black);
    }
    else{
        promptNo.setColor(Color::Red);
        promptYes.setColor(Color::Black);
    }
}

FloatRect Prompt::getTextRect(short int index)
{
    if (index != 0 && index != 1 && index != -1) {
        throw std::out_of_range("out-of-bounds parameter for getTextRect function");
    }
    if (index == 0) {
        return promptNo.getGlobalBounds();
    }
    else if(index == 1){
        return promptYes.getGlobalBounds();
    }
    else { // -1
        return promptBox.getGlobalBounds();
    }
}
