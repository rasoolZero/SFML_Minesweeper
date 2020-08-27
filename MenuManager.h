#ifndef MenuManager_h
#define MenuManager_h
#include "Screen.h"
#include "Prompt.h"
#include "SelectBox.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;

class ManagerManager;

class MenuManager : public Screen
{
private:
	short int selectedFontSize = 48;
	Text options[4];
	IntRect optionBoxes[4];
	SelectBox selectBoxes[4];

	enum class SelectedOption { play, settings, leaderboard, exit };
	SelectedOption selectedOption = SelectedOption::play;

	void draw();
	void drawPlay();
	void drawSettings();
	void drawLeaderBoard();
	void drawExit();
	void drawTitle();

    bool prompting=false;
	IntRect promptOptionBoxes[2];
    Prompt prompt;

	void setSelectedOption(SelectedOption selectedOption);
	void setSelectedOption(short int selectedOptionIndex);
protected:
	virtual void drawSelected(); //from screen
public:
	SelectedOption getSelectedOption() { return this->selectedOption; }

	virtual void update(); //from Screen
	virtual void manageInput(Keyboard::Key key); //from Screen
	virtual void manageInput(Mouse::Button button, bool released = 0); //from Screen
	virtual void updateMouse(); //from screen
	MenuManager(RenderWindow& window, ManagerManager& manager_ref);
};
#endif // !MenuManager_h


