#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "ManagerManager.h"
#include "GameManager.h"
#include "MenuManager.h"
#include "Settings.h"
using namespace sf;



int main() {
    RenderWindow window(VideoMode::getDesktopMode(), "SFML_Minesweeper", Style::Fullscreen);
    window.setVerticalSyncEnabled(true);
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
