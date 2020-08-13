#include "ManagerManager.h"

ManagerManager::ManagerManager(RenderWindow* window_ptr, MenuManager* menuManager_ptr, Settings* settings_ptr)
	:window_ptr(window_ptr)
	,menuManager_ptr(menuManager_ptr)
	,settings_ptr(settings_ptr)
{

}

ManagerManager::ManagerManager(RenderWindow* window_ptr)
	:window_ptr(window_ptr)
{

}

void ManagerManager::setPointers(MenuManager* menuManager_ptr, Settings* settings_ptr)
{
	this->menuManager_ptr = menuManager_ptr;
	this->settings_ptr = settings_ptr;
}

void ManagerManager::manage()
{
	update();
	//checkEvents();
}

void ManagerManager::setState(State state)
{
	this->state = state;
}

void ManagerManager::update()
{
	switch (state){
	//case State::game:
	/*case State::menu: {
		break; //this or default?
	}*/
	case State::settings: {
		settings_ptr->update();
		break;
	}
	//case State::leaderboard:
	default: //menu
		menuManager_ptr->update();
	}
}
