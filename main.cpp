#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "ManagerManager.h"
#include "GameManager.h"
#include "MenuManager.h"
#include "Settings.h"
#include "DotZero.h"
using namespace sf;

int main() {
    RenderWindow window(VideoMode::getDesktopMode(), "SFML_Minesweeper", Style::Fullscreen);
    Cursor cursor;
    Image image;
    if(image.loadFromFile("images\\cursor.png")){
        cursor.loadFromPixels(image.getPixelsPtr(),image.getSize(),Vector2u(0,0));
        window.setMouseCursor(cursor);
        window.setMouseCursorVisible(true);
    }
    window.setVerticalSyncEnabled(true);
    SoundManager soundManager;
    ManagerManager manager(&window);
    DotZero dotZero(window,manager);
    Leaderboard leaderboard(window, manager);
    GameManager gameManager(window, manager, soundManager,leaderboard);
    MenuManager menu(window, manager);
    Settings settings(window, manager,soundManager,leaderboard);
    manager.setPointers(&gameManager, &settings, &leaderboard, &menu,&dotZero);
    soundManager.play(SoundManager::MenuMusic);
    manager.manage();
	return 0;
}
