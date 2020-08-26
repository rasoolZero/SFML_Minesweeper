#ifndef GameManager_h
#define GameManager_h
#include <SFML/Window.hpp>
#include "Screen.h"
#include "Grid.h"
#include "Leaderboard.h"
#include "SoundManager.h"
#include "CustomOptions.h"
#include "TextBox.h"

class ManagerManager;

class GameManager : public Screen
{
public:
	GameManager(RenderWindow& window_ref, ManagerManager& manager_ref, SoundManager& soundManager_ref,Leaderboard & _leaderboard_ref);

	enum State {difficultySelection,customSelection, playing, finished};
	void setState(State state) { this->state = state; }
	virtual void update(); // from Screen
	virtual void manageInput(Keyboard::Key key); //from Screen
	virtual void manageInput(Mouse::Button button, bool released = 0); //from Screen
	virtual void updateMouse(); //from screen
	void pushChar(char input);
	void startTimer();
	void stopTimer();

private:
	State state = State::difficultySelection;

	SoundManager& soundManager_ref;
	Leaderboard& leaderboard_ref;
	Text options[5];
	IntRect optionBoxes[5];
	short int selectedFontSize = 48;

	enum Difficulty { easy, medium, hard, custom};
	Difficulty difficulty = Difficulty::easy;
	void setDifficulty(Difficulty difficulty) { this->difficulty = difficulty; }
	void setDifficulty(short int difficulty) { this->difficulty = static_cast<Difficulty>(difficulty); }
	void drawDifficulty();

	void drawGame();

    void drawTimer();
    void drawBombCount();
    void drawRestart();
    void drawGameOver();
    void drawBack();

    string timeToString(Time t);

	void checkClick();
	void reset(bool isHighScore = false);
	void startGame();

	Clock timer;
	Time score;
	bool won;
	bool hasHighScore;
	bool timerStarted;
	Text result;
	Text highScoreMessage;
	Text back;
	RectangleShape resultFrame;
	TextBox highScoreName;
    RectangleShape arrow;
    Texture arrowTexture;
    Texture redArrowTexture;

	CustomOptions customOptions;

	Grid grid;
	void setGrid();
};

#endif // !GameManager_h


