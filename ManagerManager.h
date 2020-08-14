#ifndef ManagerManager_h
#define ManagerManager_h
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Screen.h"
#include "MenuManager.h"
#include "Settings.h"
#include "Leaderboard.h"
using namespace sf;

class ManagerManager //the ultimate manager, manager of managers (manages game state and events)
{
public:
	enum State { game, settings, leaderboard, menu };

	ManagerManager(RenderWindow* window_ptr, Settings* settings_ptr, Leaderboard* leaderboard_ptr, MenuManager* menuManager_ptr);
	ManagerManager(RenderWindow* window_ptr);

	void setPointers(/*GameManager* gameManager_ptr, */Settings* settings_ptr, Leaderboard* leaderboard_ptr, MenuManager* menuManager_ptr);

	void manage();
	void setState(State state = State::menu);
private:
	RenderWindow* window_ptr;
	Screen* screen_ptr[4];

	State state = State::menu;
	int State_to_int() { return static_cast<int>(this->state); }
	void checkEvents();
	void update();


};

#endif // !ManagerManager_h


