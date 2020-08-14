#include "ManagerManager.h"

ManagerManager::ManagerManager(/*GameManager* gameManager_ptr, */RenderWindow* window_ptr, Settings* settings_ptr, Leaderboard* leaderboard_ptr, MenuManager* menuManager_ptr)
	:window_ptr(window_ptr)
	, screen_ptr{/*gameManager_ptr, */settings_ptr, leaderboard_ptr, menuManager_ptr}
{

}

ManagerManager::ManagerManager(RenderWindow* window_ptr)
	:window_ptr(window_ptr)
{

}

void ManagerManager::setPointers(/*GameManager* gameManager_ptr, */Settings* settings_ptr, Leaderboard* leaderboard_ptr, MenuManager* menuManager_ptr)
{
	//this->screen_ptr[0] = gameManager_ptr;
	this->screen_ptr[1] = settings_ptr;
	this->screen_ptr[2] = leaderboard_ptr;
	this->screen_ptr[3] = menuManager_ptr;
}

void ManagerManager::manage()
{
	//update();
	checkEvents();
}

void ManagerManager::setState(State state)
{
	this->state = state;
}

void ManagerManager::checkEvents()
{
	bool isFocused;
	isFocused = true;
	while (window_ptr->isOpen())
	{
		Event event;
		while (window_ptr->pollEvent(event))
		{
			if (event.type == Event::Closed)
				window_ptr->close();
			else if (event.type == Event::GainedFocus) {
				isFocused = true;
			}
			else if (event.type == Event::LostFocus) {
				isFocused = false;
			}

			else if (event.type == Event::KeyPressed) {
				screen_ptr[State_to_int()]->manageInput(event.key.code);
			}
		}


		if (isFocused) {
			window_ptr->clear(Color(235, 235, 250));
			update();
			window_ptr->display();
		}
	}
}

void ManagerManager::update()
{
	screen_ptr[State_to_int()]->update();
}
