#include "MenuManager.h"

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
			if (currentSize != normalFontSize) {
				options[i].setCharacterSize(currentSize - 1);
			}
		}
	}
	drawPlay();
	drawLeaderBoard();
	drawSettings();
	drawExit();
}

void MenuManager::drawPlay()
{
	
	this->window_ref.draw(options[0]);
}

void MenuManager::drawSettings()
{
	this->window_ref.draw(options[1]);
}

void MenuManager::drawLeaderBoard()
{
	this->window_ref.draw(options[2]);
}

void MenuManager::drawExit()
{
	this->window_ref.draw(options[3]);
}

void MenuManager::setSelectedOption(SelectedOption selectedOption)
{
	this->selectedOption = selectedOption;

}
void MenuManager::setSelectedOption(int selectedOptionIndex)
{
	this->selectedOption = static_cast<SelectedOption>(selectedOptionIndex);

}

void MenuManager::manageInput()
{
    static bool prevUpKeyStatus = false;
    static bool prevDownKeyStatus = false;
	int selectedOptionIndex = static_cast<int>(this->selectedOption);
	if (options[selectedOptionIndex].getCharacterSize() == selectedFontSize) {

		if (Keyboard::isKeyPressed(Keyboard::Up) && !prevUpKeyStatus) {
			options[selectedOptionIndex].setFillColor(normalTextColor);
			setSelectedOption( (selectedOptionIndex += 3) %= 4 ); // goes to previous state in the cycle
		}
		else if (Keyboard::isKeyPressed(Keyboard::Down) && !prevDownKeyStatus )
		{
			options[selectedOptionIndex].setFillColor(normalTextColor);
			setSelectedOption( (selectedOptionIndex += 1) %= 4 ); // goes to next state in the cycle
		}
		options[selectedOptionIndex].setFillColor(selectedTextColor);
	}

    prevUpKeyStatus=Keyboard::isKeyPressed(Keyboard::Up);
    prevDownKeyStatus=Keyboard::isKeyPressed(Keyboard::Down);
}

void MenuManager::update()
{
	manageInput();
	draw();
}

MenuManager::MenuManager(RenderWindow& window)
	:window_ref(window)
{
	if (!font.loadFromFile("fonts\\arial.ttf")) {
		throw std::runtime_error("menu font could not be loaded\n");
	}
	options[0].setString("Play");
	options[1].setString("Settings");
	options[2].setString("Leaderboard");
	options[3].setString("Exit");
	for (int i = 0; i < 4; i++) {
		options[i].setFont(font);
		options[i].setFillColor(normalTextColor);
		options[i].setCharacterSize(normalFontSize);
		options[i].setPosition(50, window_ref.getSize().y / 2 + i * 65);
	}
}
