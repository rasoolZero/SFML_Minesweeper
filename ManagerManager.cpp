#include "ManagerManager.h"

ManagerManager::ManagerManager(RenderWindow* window_ptr, GameManager* gameManager_ptr, Settings* settings_ptr, Leaderboard* leaderboard_ptr, MenuManager* menuManager_ptr, DotZero* DotZero_ptr)
	:window_ptr(window_ptr)
	, screen_ptr{gameManager_ptr, settings_ptr, leaderboard_ptr, menuManager_ptr ,DotZero_ptr}
{

}

ManagerManager::ManagerManager(RenderWindow* window_ptr)
	:window_ptr(window_ptr)
{

}

void ManagerManager::setPointers(GameManager* gameManager_ptr, Settings* settings_ptr, Leaderboard* leaderboard_ptr, MenuManager* menuManager_ptr, DotZero* DotZero_ptr)
{
	this->screen_ptr[0] = gameManager_ptr;
	this->screen_ptr[1] = settings_ptr;
	this->screen_ptr[2] = leaderboard_ptr;
	this->screen_ptr[3] = menuManager_ptr;
	this->screen_ptr[4] = DotZero_ptr;
}

void ManagerManager::manage()
{
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
			if (isFocused) {
				if (event.type == Event::MouseMoved) {
					screen_ptr[State_to_int()]->updateMouse();
				}
				else if (event.type == Event::KeyPressed) {
					screen_ptr[State_to_int()]->manageInput(event.key.code);
				}
				else if (event.type == Event::TextEntered) {
					if (event.text.unicode < 128 && State_to_int() == 0) { //ASCII only, gameManager only
						dynamic_cast<GameManager*>(screen_ptr[State_to_int()])->pushChar(static_cast<char>(event.text.unicode));
					}
				}
				else if (event.type == Event::MouseButtonPressed) {
					screen_ptr[State_to_int()]->manageInput(event.mouseButton.button);
				}
				else if (event.type == Event::MouseButtonReleased) {
					screen_ptr[State_to_int()]->manageInput(event.mouseButton.button, true);
				}
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
