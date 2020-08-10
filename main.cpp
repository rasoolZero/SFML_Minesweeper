#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

bool isFocused;

int main() {



    sf::RenderWindow window(VideoMode::getFullscreenModes()[0], "SFML_Minesweeper", Style::Fullscreen);
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {

            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == Event::GainedFocus)
                isFocused=true;
            if (event.type == Event::LostFocus)
                isFocused=false;
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) { //close the window on ESC keypress
                window.close();
            }
        }

        window.clear(Color::White);
        if(isFocused){
            //update
        }
        window.display();

    }
	return 0;
}
