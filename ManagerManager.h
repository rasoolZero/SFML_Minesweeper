#ifndef ManagerManager_h
#define ManagerManager_h
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Screen.h"
#include "GameManager.h"
#include "MenuManager.h"
#include "Settings.h"
#include "Leaderboard.h"
#include "DotZero.h"
using namespace sf;

class ManagerManager //the ultimate manager, manager of managers (manages game state and events)
{
public:
	enum State { game, settings, leaderboard, menu, dotzero };

	ManagerManager(RenderWindow* window_ptr, GameManager* gameManager_ptr, Settings* settings_ptr, Leaderboard* leaderboard_ptr, MenuManager* menuManager_ptr, DotZero* DotZero_ptr);
	ManagerManager(RenderWindow* window_ptr);

	void setPointers(GameManager* gameManager_ptr, Settings* settings_ptr, Leaderboard* leaderboard_ptr, MenuManager* menuManager_ptr, DotZero* DotZero_ptr);

	void manage();
	void setState(State state = State::menu);
private:
	RenderWindow* window_ptr;
	Screen* screen_ptr[5];

	State state = State::dotzero;
	int State_to_int() { return static_cast<int>(this->state); }
	void checkEvents();
	void update();


};

#endif // !ManagerManager_h


