#ifndef TextBox_h
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;
class TextBox : public RectangleShape
{
public:
	TextBox(Vector2f position, short int  fontSize, Font& font, short int limit = 16);
	string getContent() { return this->content; }
	void manageInput(char key);
	void draw(RenderTarget& target);
	void reset();
private:
	Text text;
	string content;
	short int charLimit;
	short int fontSize;
};

#endif // !TextBox_h


