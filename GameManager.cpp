#include "GameManager.h"
#include "ManagerManager.h"

GameManager::GameManager(RenderWindow& window_ref, ManagerManager& manager_ref, SoundManager& soundManager_ref)
	:Screen(window_ref, manager_ref, "fonts\\arial.ttf")
	,soundManager_ref(soundManager_ref)
	,grid{getWindow_ref(), soundManager_ref }
{
	options[0].setString("easy");
	options[1].setString("medium");
	options[2].setString("hard");
	options[3].setString("custom");
	options[4].setString("back");
	for (int i = 0; i < 5; i++) {
		options[i].setFont(getFont());
		if (i) {
			options[i].setFillColor(getNormalTextColor());
		}
		options[i].setCharacterSize(getNormalFontSize());
		if (i != 4) {
			options[i].setPosition(70, getWindow_ref().getSize().y / 2 + i * 65);
		}
	}
	options[0].setFillColor(getSelectedTextColor());
	options[4].setPosition(50, getWindow_ref().getSize().y - 90);
}

void GameManager::update()
{
	if (state == State::difficultySelection) {
		drawDifficulty();
	}
	else { //state : playing
		drawGame();
	}
}

void GameManager::drawDifficulty()
{
	for (int i = 0; i < 5; i++)
	{
		short int currentSize = options[i].getCharacterSize();
		if (i == static_cast<int>(difficulty)) {
			if (currentSize != selectedFontSize) {
				options[i].setCharacterSize(currentSize + 1);
			}
		}
		else {
			if (currentSize != getNormalFontSize()) {
				options[i].setCharacterSize(currentSize - 1);
			}
		}
		getWindow_ref().draw(options[i]);
	}

}

void GameManager::drawGame()
{
	grid.update();
}

void GameManager::manageInput(Keyboard::Key key)
{
	int selectedOptionIndex = static_cast<int>(this->difficulty);
	if (options[selectedOptionIndex].getCharacterSize() == selectedFontSize) {

		if (key == Keyboard::Up) {
			options[selectedOptionIndex].setFillColor(getNormalTextColor());
			setDifficulty((selectedOptionIndex += 4) %= 5); // goes to previous state in the cycle
		}
		else if (key == Keyboard::Down)
		{
			options[selectedOptionIndex].setFillColor(getNormalTextColor());
			setDifficulty((selectedOptionIndex += 1) %= 5); // goes to next state in the cycle
		}
	}
	 if (key == Keyboard::Escape || ( (key == Keyboard::Enter || key == Keyboard::Space) && selectedOptionIndex == 4)) { //back
		options[selectedOptionIndex].setFillColor(getNormalTextColor());
		difficulty = Difficulty::easy;
		options[selectedOptionIndex].setCharacterSize(getNormalFontSize());
		selectedOptionIndex = 0;

		setState(State::difficultySelection);
		getManager_ref().setState();
	}
	else if (key == Keyboard::Enter || key == Keyboard::Space) {
		if (difficulty == Difficulty::easy) {
			grid.setupGrid(9, 9);
		}
		else if (difficulty == Difficulty::medium) {
			grid.setupGrid(16, 16, 40);
		}
		else if (difficulty == Difficulty::hard) {
			grid.setupGrid(30, 16, 99);
		}
		else { //custom
			return; //temporary until cutom is added
		}
		setState(State::playing);
	}
	options[selectedOptionIndex].setFillColor(getSelectedTextColor());
}
