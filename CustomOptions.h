#ifndef CustomOptions_h
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
using namespace sf;

class CustomOptions : public Transformable
{
public:
	CustomOptions(RenderWindow& window_ref, Font& font);
	void moveGroup(float x, float y);
	void setGroupPosition(Vector2f position);
	void draw();
	void setSelectedOption(short int selectedOptionIndex);
	void manageInput(Keyboard::Key key);
	void reset();

	short int getWidth() { return this->customAmounts[0]; }
	short int getHeight() { return this->customAmounts[1]; }
	short int getBombCount() { return this->customAmounts[2]; }
private:
	Text customTexts[3]; //modifiable value
	short int customAmounts[3];

	Text limits[6];
	short int limits_amount[6];

	RectangleShape textBoxes[3]; //frame for modifiable values

	Text descriptions[3];

	RenderWindow& window_ref;

	enum SelectedOption { width, height, bombCount };
	SelectedOption selectedOption = SelectedOption::width;
	Color selectedRectColor = Color(250, 0, 0);
	Color normalRectColor = Color::Black;
};

#endif // !CustomOptions_h


