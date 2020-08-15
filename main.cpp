#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "ManagerManager.h"
#include "MenuManager.h"
#include "Settings.h"
using namespace sf;



int main() {
    RenderWindow window(VideoMode::getDesktopMode(), "SFML_Minesweeper", Style::Fullscreen);
    SoundManager soundManager;
    window.setVerticalSyncEnabled(true);
    ManagerManager manager(&window);
    MenuManager menu(window, manager);
    Leaderboard leaderboard(window, manager);
    Settings settings(window, manager,soundManager);
    manager.setPointers(&settings, &leaderboard, &menu);
    soundManager.play(SoundManager::MenuMusic);

    manager.manage();
	return 0;
}
