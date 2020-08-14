#include "MenuManager.h"
#include "ManagerManager.h"

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

void MenuManager::setSelectedOption(SelectedOption selectedOption)
{
	this->selectedOption = selectedOption;

}
void MenuManager::setSelectedOption(short int selectedOptionIndex)
{
	this->selectedOption = static_cast<SelectedOption>(selectedOptionIndex);

}

void MenuManager::manageInput()
{
    static bool prevUpKeyStatus = false;
    static bool prevDownKeyStatus = false;
	static bool prevToggleKeyStatus = false; //for Enter and Space keys

	int selectedOptionIndex = static_cast<int>(this->selectedOption);
	if (options[selectedOptionIndex].getCharacterSize() == selectedFontSize) {

		if (Keyboard::isKeyPressed(Keyboard::Up) && !prevUpKeyStatus) {
			options[selectedOptionIndex].setFillColor(getNormalTextColor());
			setSelectedOption( (selectedOptionIndex += 3) %= 4 ); // goes to previous state in the cycle
		}
		else if (Keyboard::isKeyPressed(Keyboard::Down) && !prevDownKeyStatus )
		{
			options[selectedOptionIndex].setFillColor(getNormalTextColor());
			setSelectedOption( (selectedOptionIndex += 1) %= 4 ); // goes to next state in the cycle
		}
		if ((Keyboard::isKeyPressed(Keyboard::Enter) || Keyboard::isKeyPressed(Keyboard::Space)) && !prevToggleKeyStatus) {
			getManager_ref().setState(static_cast<ManagerManager::State>(this->selectedOption));
		}
		options[selectedOptionIndex].setFillColor(getSelectedTextColor());
	}

    prevUpKeyStatus=Keyboard::isKeyPressed(Keyboard::Up);
    prevDownKeyStatus=Keyboard::isKeyPressed(Keyboard::Down);
	prevToggleKeyStatus = Keyboard::isKeyPressed(Keyboard::Enter) | Keyboard::isKeyPressed(Keyboard::Space);
}

void MenuManager::update()
{
	manageInput();
	draw();
}

MenuManager::MenuManager(RenderWindow& window, ManagerManager& manager_ref)
	:Screen(window, manager_ref, "fonts\\arial.ttf", 40)
{
	
	options[0].setString("Play");
	options[1].setString("Settings");
	options[2].setString("Leaderboard");
	options[3].setString("Exit");
	for (int i = 0; i < 4; i++) {
		options[i].setFont(getFont());
		options[i].setFillColor(getNormalTextColor());
		options[i].setCharacterSize(getNormalFontSize());
		options[i].setPosition(50, getWindow_ref().getSize().y / 2 + i * 65);
	}
}
