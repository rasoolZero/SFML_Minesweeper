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
	drawSelected();
	drawPlay();
	drawLeaderBoard();
	drawSettings();
	drawExit();
	drawTitle();
	if(prompting)
        getWindow_ref().draw(prompt);
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
    text.setColor(Color(180,180,180));
    getWindow_ref().draw(text);
}

void MenuManager::drawSelected()
{
	short int selected;
	if (getHover() != -1) {
		selected = getHover();
	}
	else {
		selected = static_cast<short int>(selectedOption);
	}
	for (int i = 0; i < 4; i++)
	{
		if (i == selected) {
			if (getHover() != -1) {
				selectBoxes[i].select(Mouse::getPosition().x);
			}
			else {
				selectBoxes[i].select();
			}
		}
		else {
			selectBoxes[i].deselect();
		}
		if (selectBoxes[i].getAlpha()) {
			getWindow_ref().draw(selectBoxes[i]);
		}
	}
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
    if(prompting){
        if(key==Keyboard::Right || key==Keyboard::Left)
            prompt.changeOption();
        if(key==Keyboard::Space || key==Keyboard::Enter){
            if(prompt.getState())
                getWindow_ref().close();
			else {
                prompting=false;
				prompt.setState(0);
			}
        }
		if (key == Keyboard::Escape) {
            prompting=false;
			prompt.setState(0);
		}
        return;
    }

	int selectedOptionIndex = static_cast<int>(this->selectedOption);
	if (options[selectedOptionIndex].getCharacterSize() == selectedFontSize) {

		if (key == Keyboard::Up) {
			options[selectedOptionIndex].setFillColor(getNormalTextColor());
			setSelectedOption( (selectedOptionIndex += 3) %= 4 ); // goes to previous state in the cycle
			setHover(-1);
		}
		else if (key == Keyboard::Down)
		{
			options[selectedOptionIndex].setFillColor(getNormalTextColor());
			setSelectedOption( (selectedOptionIndex += 1) %= 4 ); // goes to next state in the cycle
			setHover(-1);
		}
		else if (key == Keyboard::Enter || key == Keyboard::Space) {
            if(selectedOption == SelectedOption::exit)
                prompting=true;
			getManager_ref().setState(static_cast<ManagerManager::State>(this->selectedOption));
		}
		else if(key == Keyboard::Escape)
            prompting=true;
		options[selectedOptionIndex].setFillColor(getSelectedTextColor());
	}
}

void MenuManager::manageInput(Mouse::Button button, bool released)
{
	if (released) {
		return;
	}
	if (button == Mouse::Left) {
		if (!prompting) {
			for (int i = 0; i < 4; i++)
			{
				if (optionBoxes[i].contains(Mouse::getPosition())) {
					if (i == static_cast<int>(SelectedOption::exit)) {
						setHover(-1);
						prompting = true;
					}
					options[static_cast<int>(selectedOption)].setFillColor(getNormalTextColor());
					setSelectedOption(i);
					options[i].setFillColor(getSelectedTextColor());
					getManager_ref().setState(static_cast<ManagerManager::State>(i));
					break;
				}
			}
		}
		else {
			for (int i = 0; i < 2; i++)
			{
				if (promptOptionBoxes[i].contains(Mouse::getPosition())) {
					if (i) { //yes option
						getWindow_ref().close();
					}
					else {
						prompting = false;
					}
				}
			}
		}
	}
}

void MenuManager::updateMouse()
{
	if (!prompting) {
		int selectedOptionIndex = static_cast<int>(this->selectedOption);
		options[selectedOptionIndex].setFillColor(getNormalTextColor());
		for (int i = 0; i < 4; i++)
		{
			if (optionBoxes[i].contains(Mouse::getPosition())) {
				setSelectedOption(i);
				selectedOptionIndex = i;
				setHover(i);
				break;
			}
			setHover(-1);
		}
		options[selectedOptionIndex].setFillColor(getSelectedTextColor());
	}
	else {
		for (int i = 0; i < 2; i++)
		{
			if (promptOptionBoxes[i].contains(Mouse::getPosition())) {
				prompt.setState(i);
			}
		}
	}
}

void MenuManager::update()
{
	draw();
}

MenuManager::MenuManager(RenderWindow& window, ManagerManager& manager_ref)
	:Screen(window, manager_ref, "fonts\\Roboto-Light.ttf", 40),
	prompt(window,getFont())
	,selectBoxes{Color::White, Color::White, Color::White, Color::White }
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
	for (int i = 0; i < 4; i++)
	{
		optionBoxes[i].top = options[i].getGlobalBounds().top - 10;
		optionBoxes[i].left = options[i].getGlobalBounds().left - 30;
		optionBoxes[i].width = 300;
		optionBoxes[i].height = options[i].getGlobalBounds().height + 30;
	}
	for (int i = 0; i < 4; i++)
	{
		selectBoxes[i].setBox(optionBoxes[i]);
		if (i) {
			selectBoxes[i].setAlpha(0);
		}
	}
	for (int i = 0; i < 2; i++)
	{
		promptOptionBoxes[i].top = prompt.getTextRect(i).top - 10;
		promptOptionBoxes[i].height = prompt.getTextRect(i).height + 20;
		promptOptionBoxes[i].width = prompt.getTextRect(-1).width / 2;
	}
	promptOptionBoxes[0].left = prompt.getTextRect(-1).left;
	promptOptionBoxes[1].left = prompt.getTextRect(-1).left + prompt.getTextRect(-1).width / 2;
}
