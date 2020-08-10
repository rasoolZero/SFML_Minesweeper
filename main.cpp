#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "MenuManager.h"
using namespace sf;

int main() {
    
    RenderWindow window(VideoMode::getDesktopMode(), "SFML_Minesweeper", Style::Fullscreen);
    MenuManager menu(window);
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) { //close the window on ESC keypress
                window.close();
            }
        }

        window.clear(Color(235, 235, 250));
        menu.update();
        window.display();
        sleep(milliseconds(5));
    }
	return 0;
}
