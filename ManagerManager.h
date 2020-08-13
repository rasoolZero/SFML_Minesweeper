#ifndef ManagerManager_h
#define ManagerManager_h
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "MenuManager.h"
#include "Settings.h"
using namespace sf;

class ManagerManager //the ultimate manager, manager of managers (manages game state and events)
{
public:
	enum State { game, settings, leaderboard, menu };

	ManagerManager(RenderWindow* window_ptr, MenuManager* menuManager_ptr, Settings* settings_ptr);
	ManagerManager(RenderWindow* window_ptr);

	void setPointers(MenuManager* menuManager_ptr, Settings* settings_ptr);

	void manage();
	void setState(State state = State::menu);
private:
	RenderWindow* window_ptr;
	MenuManager* menuManager_ptr;
	Settings* settings_ptr;

	State state = State::menu;
	void checkEvents();
	void update();


};

#endif // !ManagerManager_h


