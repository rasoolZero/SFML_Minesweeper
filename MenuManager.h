#ifndef MenuManager_h

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;
class MenuManager
{
private:
	//GameManager& gameManager_ref
	RenderWindow& window_ref;
	//ScoreManager& scoreManager_ref;
	//Settings& settings_ref;

	bool state;

	short int fontSize;
	Font font;
	Text options[4];

	Color selectedTextColor = Color(255, 0, 0);
	Color normalTextColor = Color::Black;

	enum SelectedOption { play, settings, leaderboard, exit };
	SelectedOption selectedOption = SelectedOption::play;

	void draw();
	void drawPlay();
	void drawSettings();
	void drawLeaderBoard();
	void drawExit();

	void setState(bool state) { this->state = state; }
	void setSelectedOption(SelectedOption selectedOption);
	void manageInput();
public:
	bool getState() { return this->state; }

	void setFontSize(short int fontSize) { this->fontSize = fontSize; }
	short int getFontSize() { return this->fontSize; }

	SelectedOption getSelectedOption() { return this->selectedOption; }

	void update();
	MenuManager(RenderWindow& window);
};
#endif // !MenuManager_h


