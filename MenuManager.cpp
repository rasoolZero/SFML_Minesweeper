#include "MenuManager.h"

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

void MenuManager::manageInput()
{	
	if(Keyboard::isKeyPressed(Keyboard::Up)){
		options[static_cast<int>(selectedOption)].setFillColor(normalTextColor);
		setSelectedOption((SelectedOption)(((int)this->selectedOption + 3) % 4)); // goes to previous state in the cycle
	}
	else if (Keyboard::isKeyPressed(Keyboard::Down))
	{
		options[static_cast<int>(selectedOption)].setFillColor(normalTextColor);
		setSelectedOption((SelectedOption)(((int)this->selectedOption + 1) % 4)); // goes to next state in the cycle
	}
	options[static_cast<int>(selectedOption)].setFillColor(selectedTextColor);
}

void MenuManager::update()
{
	manageInput();
	drawPlay();
	drawLeaderBoard();
	drawSettings();
	drawExit();
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
		options[i].setCharacterSize(40);
		options[i].setPosition(50, window_ref.getSize().y / 2 + i * 60);
	}
}
