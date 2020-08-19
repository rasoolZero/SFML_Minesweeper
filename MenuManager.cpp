#include "MenuManager.h"
#include "ManagerManager.h"
using namespace sf;

void MenuManager::draw()
{
	for (int i = 0; i < 4; i++)
	{
		short int currentSize = options[i].getCharacterSize();
		if (i == static_cast<int>(selectedOption)) {
			if (currentSize != selectedFontSize) {
				options[i].setCharacterSize(currentSize + 1);
			}
		}
		else {
			if (currentSize != getNormalFontSize()) {
				options[i].setCharacterSize(currentSize - 1);
			}
		}
	}
	drawPlay();
	drawLeaderBoard();
	drawSettings();
	drawExit();
	drawTitle();
	if(prompt)
        drawPrompt();
}

void MenuManager::drawPlay()
{

	this->getWindow_ref().draw(options[0]);
}

void MenuManager::drawSettings()
{
	this->getWindow_ref().draw(options[1]);
}

void MenuManager::drawLeaderBoard()
{
	this->getWindow_ref().draw(options[2]);
}

void MenuManager::drawExit()
{
	this->getWindow_ref().draw(options[3]);
}
void MenuManager::drawTitle(){
    Text text("SFML\nMinesweeper",getFont(),60);
    text.setPosition(50,20);
    text.setColor(Color(20,20,40));
    getWindow_ref().draw(text);
}

void MenuManager::setSelectedOption(SelectedOption selectedOption)
{
	this->selectedOption = selectedOption;

}
void MenuManager::setSelectedOption(short int selectedOptionIndex)
{
	this->selectedOption = static_cast<SelectedOption>(selectedOptionIndex);

}

void MenuManager::manageInput(Keyboard::Key key)
{
    if(prompt){
        if(key==Keyboard::Right || key==Keyboard::Left)
            promptOption=!promptOption;
        if(key==Keyboard::Space || key==Keyboard::Enter){
            if(promptOption)
                getWindow_ref().close();
            else
                prompt=false;
        }
        return;
    }

	int selectedOptionIndex = static_cast<int>(this->selectedOption);
	if (options[selectedOptionIndex].getCharacterSize() == selectedFontSize) {

		if (key == Keyboard::Up) {
			options[selectedOptionIndex].setFillColor(getNormalTextColor());
			setSelectedOption( (selectedOptionIndex += 3) %= 4 ); // goes to previous state in the cycle
		}
		else if (key == Keyboard::Down)
		{
			options[selectedOptionIndex].setFillColor(getNormalTextColor());
			setSelectedOption( (selectedOptionIndex += 1) %= 4 ); // goes to next state in the cycle
		}
		else if (key == Keyboard::Enter || key == Keyboard::Space) {
            if(selectedOption == SelectedOption::exit)
                prompt=true;
			getManager_ref().setState(static_cast<ManagerManager::State>(this->selectedOption));
		}
		else if (key == Keyboard::Escape) {
			getWindow_ref().close();
			return;
		}
		options[selectedOptionIndex].setFillColor(getSelectedTextColor());
	}
}

void MenuManager::update()
{
	//manageInput();
	draw();
}

MenuManager::MenuManager(RenderWindow& window, ManagerManager& manager_ref)
	:Screen(window, manager_ref, "fonts\\Roboto-Light.ttf", 40)
{

	options[0].setString("Play");
	options[1].setString("Settings");
	options[2].setString("Leaderboard");
	options[3].setString("Exit");
	short int startingPoint = getWindow_ref().getSize().y / 2;
	for (int i = 0; i < 4; i++) {
		options[i].setFont(getFont());
		if (i) {
			options[i].setFillColor(getNormalTextColor());
		}
		options[i].setCharacterSize(getNormalFontSize());
		options[i].setPosition(50, startingPoint + i * 65);
	}
	options[0].setFillColor(getSelectedTextColor());
	setupPromptBox();
}

void MenuManager::setupPromptBox(){
    promptYes = Text("Yes",getFont(),24);
    promptNo = Text("No",getFont(),24);
    promptText = Text("Are You Sure?",getFont(),24);

    FloatRect textRect = promptYes.getLocalBounds();
    promptYes.setOrigin(promptYes.getOrigin().x,
        textRect.top  + textRect.height/2.0f);

    promptYes.setPosition(Vector2f(getWindow_ref().getSize().x/2.0f + 20,getWindow_ref().getSize().y/2.0f+ 15 ));


    textRect = promptNo.getLocalBounds();
    promptNo.setOrigin(promptNo.getOrigin().x,
        textRect.top  + textRect.height/2.0f);

    promptNo.setPosition(Vector2f(getWindow_ref().getSize().x/2.0f - promptNo.getGlobalBounds().width-20,getWindow_ref().getSize().y/2.0f + 15));


    textRect = promptText.getLocalBounds();
    promptText.setOrigin(textRect.left + textRect.width/2.0f,
        textRect.top  + textRect.height/2.0f);

    promptText.setPosition(Vector2f(getWindow_ref().getSize().x/2.0f , getWindow_ref().getSize().y/2.0f - 25));

    promptText.setColor(Color::Black);


    promptBox.setSize(Vector2f (promptText.getGlobalBounds().width+10, textRect.height + promptNo.getGlobalBounds().height+50));
    promptBox.setFillColor(Color(250,250,250,100));
    promptBox.setOutlineColor(Color::Black);
    promptBox.setOutlineThickness(3);
    promptBox.setPosition(Vector2f ( getWindow_ref().getSize().x/2.0f - promptBox.getSize().x/2.0f , getWindow_ref().getSize().y/2.0f - promptBox.getSize().y/2.0f ) );

}
void MenuManager::drawPrompt(){
    if(promptOption){
        promptYes.setColor(Color::Red);
        promptNo.setColor(Color::Black);
    }
    else{
        promptNo.setColor(Color::Red);
        promptYes.setColor(Color::Black);
    }
    getWindow_ref().draw(promptBox);
    getWindow_ref().draw(promptYes);
    getWindow_ref().draw(promptNo);
    getWindow_ref().draw(promptText);
}
