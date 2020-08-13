#ifndef CheckBox_h
#define CheckBox_h
#include <SFML/Graphics.hpp>
using namespace sf;
class CheckBox : public RectangleShape
{
private:
	bool state = false;
	Texture checked;
	Texture unchecked;
public:
	void setState(bool state);
	bool getState() { return this->state; }
	void swtitchState();

	CheckBox(short int length, Vector2f position, Texture& unchecked, Texture& checked);
	CheckBox();
};

#endif // !CheckBox_h


