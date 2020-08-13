#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "ManagerManager.h"
#include "MenuManager.h"
#include "Settings.h"
using namespace sf;

bool isFocused;

int main() {
    isFocused = true;
    RenderWindow window(VideoMode::getDesktopMode(), "SFML_Minesweeper", Style::Fullscreen);
    window.setVerticalSyncEnabled(true);
    ManagerManager manager(&window);
    MenuManager menu(window, manager);
    Leaderboard leaderboard(window, manager);
    Settings settings(window, manager);
    manager.setPointers(&menu, &settings, &leaderboard);
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::GainedFocus) {
                isFocused = true;
            }
            if (event.type == Event::LostFocus) {
                isFocused = false;
            }

            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) { //close the window on ESC keypress
                window.close();
            }
        }
        
        
        if (isFocused) {
            window.clear(Color(235, 235, 250));
            manager.manage();
            window.display();
        }
    }
	return 0;
}
