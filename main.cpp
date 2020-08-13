#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "MenuManager.h"
#include "Settings.h"
using namespace sf;

bool isFocused;

int main() {
    isFocused = true;
    RenderWindow window(VideoMode::getDesktopMode(), "SFML_Minesweeper", Style::Fullscreen);
    window.setVerticalSyncEnabled(true);
    MenuManager menu(window);

    Settings settings(window, menu);

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
            //menu.update();
            settings.update();
            window.display();
        }
    }
	return 0;
}
