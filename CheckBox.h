#ifndef CheckBox_h
#define CheckBox_h
#include <SFML/Graphics.hpp>
//#include <SFML/Window.hpp>
using namespace sf;
class CheckBox : public RectangleShape
{
private:
	bool state;
	Texture checked;
	Texture unchecked;
public:
	void setState(bool state);
	bool getState() { return this->state; }

	CheckBox(short int length, Vector2f position, Texture& unchecked, Texture& checked);
};

#endif // !CheckBox_h


