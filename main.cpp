#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "ManagerManager.h"
#include "GameManager.h"
#include "MenuManager.h"
#include "Settings.h"
using namespace sf;

void DotZero(RenderWindow & window){

    Font font;
    if(!font.loadFromFile("fonts\\Roboto-Light.ttf"))
		throw std::runtime_error("font could not be loaded\n");

    Text text("DotZero",font,50);
    text.setStyle(Text::Bold);
    text.setFillColor(Color::Black);

    FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f,
                textRect.top  + textRect.height/2.0f);
    text.setPosition(Vector2f(window.getSize().x/2.0f,window.getSize().y/2.0f));

    int alpha=0;
    bool shown=false;
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event)){
			if (event.type == Event::Closed)
				window.close();
			else if (event.type == Event::KeyPressed) {
                if(event.key.code==Keyboard::Escape || event.key.code==Keyboard::Enter || event.key.code==Keyboard::Space){
                    window.clear(Color(235, 235, 250));
                    window.display();
                    return;
                }
			}
		}
        if(shown)
            alpha-=2;
        else
            alpha+=2;
        if(alpha>=254)
            shown=true;
        if(shown && alpha <= 0)
            return;
        text.setFillColor(Color(0,0,0,alpha));
        window.clear(Color(235, 235, 250));
        window.draw(text);
        window.display();
	}
}


int main() {
    RenderWindow window(VideoMode::getDesktopMode(), "SFML_Minesweeper", Style::Fullscreen);
    window.setVerticalSyncEnabled(true);
    DotZero(window);
    SoundManager soundManager;
    ManagerManager manager(&window);
    Leaderboard leaderboard(window, manager);
    GameManager gameManager(window, manager, soundManager,leaderboard);
    MenuManager menu(window, manager);
    Settings settings(window, manager,soundManager,leaderboard);
    manager.setPointers(&gameManager, &settings, &leaderboard, &menu);
    soundManager.play(SoundManager::MenuMusic);
    manager.manage();
	return 0;
}
