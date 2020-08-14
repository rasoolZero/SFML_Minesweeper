#ifndef MenuManager_h
#define MenuManager_h
#include "Screen.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;

class ManagerManager;

class MenuManager : public Screen
{
private:
	//ManagerManager& manager_ref;
	//RenderWindow& window_ref;

	//short int normalFontSize = 40;
	short int selectedFontSize = 48;
	//Font font;
	Text options[4];

	//Color selectedTextColor = Color(255, 0, 0);
	//Color normalTextColor = Color::Black;

	enum class SelectedOption { play, settings, leaderboard, exit };
	SelectedOption selectedOption = SelectedOption::play;

	void draw();
	void drawPlay();
	void drawSettings();
	void drawLeaderBoard();
	void drawExit();

	void setSelectedOption(SelectedOption selectedOption);
	void setSelectedOption(short int selectedOptionIndex);
	void manageInput();
public:

	//void setFontSize(short int fontSize) { this->NormalFontSize = fontSize; }
	//short int getFontSize() { return this->normalFontSize; }

	SelectedOption getSelectedOption() { return this->selectedOption; }

	virtual void update();
	MenuManager(RenderWindow& window, ManagerManager& manager_ref);
};
#endif // !MenuManager_h


