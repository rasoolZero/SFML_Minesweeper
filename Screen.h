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
	virtual void manageInput(Keyboard::Key key) = 0;
	virtual void manageInput(Mouse::Button button, bool released = 0) = 0;
	virtual void update() = 0;
	virtual void updateMouse() = 0;
	Font& getFont() { return this->font; }
	Color getSelectedTextColor() { return this->selectedTextColor; }
	Color getNormalTextColor() { return this->normalTextColor; }
	short int getNormalFontSize() { return this->normalFontSize; }
	short int getHover() { return this->hover; }
	void setHover(short int hover) { this->hover = hover; }
protected:
	Screen(RenderWindow& window_ref,ManagerManager& manager_ref, std::string fontname, short int normalFontSize = 40, Color normalTextColor = Color(220, 220, 220), Color selectedTextColor = Color(210, 46, 46));
	RenderWindow& getWindow_ref() { return this->window_ref; }
	ManagerManager& getManager_ref() { return this->manager_ref; }
	void setOptionCount(short int optionCount) { this->optionCount = optionCount; }
	virtual void drawSelected() = 0;
private:
	Font font;
	short int normalFontSize;

	short int hover = -1;
	short int optionCount;

	Color normalTextColor;
	Color selectedTextColor;

	RenderWindow& window_ref;
	ManagerManager& manager_ref;
};

#endif // !Screen_h


