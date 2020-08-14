#ifndef Screen_h
#define Screen_h
#include <string>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
using namespace sf;
class ManagerManager;

class Screen
{
public:
	//virtual void manageInput(Keyboard::Key) = 0;
	virtual void update() = 0;
	Font& getFont() { return this->font; }
	Color getSelectedTextColor() { return this->selectedTextColor; }
	Color getNormalTextColor() { return this->normalTextColor; }
	short int getNormalFontSize() { return this->normalFontSize; }
protected:
	Screen(RenderWindow& window_ref,ManagerManager& manager_ref, std::string fontname, short int normalFontSize = 40, Color normalTextColor = Color::Black, Color selectedTextColor = Color::Red);
	RenderWindow& getWindow_ref() { return this->window_ref; }
	ManagerManager& getManager_ref() { return this->manager_ref; }
	//void setNormalTextColor(Color color) { this->normalTextColor = color; }
	//void setSelectedTextColor(Color color) { this->selectedTextColor = color; }
	//void setNormalFontSize(short int size) { this->normalFontSize = size; }
private:
	Font font;
	short int normalFontSize;

	Color normalTextColor;
	Color selectedTextColor;

	RenderWindow& window_ref;
	ManagerManager& manager_ref;
};

#endif // !Screen_h


