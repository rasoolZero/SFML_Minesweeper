#include "TextBox.h"

TextBox::TextBox(Vector2f position, short int  fontSize, short int limit)
	:charLimit(limit)
	,fontSize(fontSize)
{
	setOrigin(15, 0);
	setSize(Vector2f(30, fontSize + 6));
	setPosition(position);
	setOutlineColor(Color::Black);
	setOutlineThickness(3);
	setFillColor(Color(150, 150, 150, 80));

}

void TextBox::manageInput(char key)
{
	bool changed = 0;
	if (key == Keyboard::BackSpace) {
		content.pop_back();
		changed = 1;
	}
	else if ( (content.length() < charLimit) && (isalnum(key) || key == '_') ) {
		content += key;
		changed = 1;
	}
	if (changed) {
		text.setString(content);
		short int width = text.getLocalBounds().width;
		text.setOrigin(width / 2, 0);
		if (getSize().x - width < 20) {
			setSize(Vector2f(width + 20, fontSize + 6));
			setOrigin(getSize().x / 2, 0);
		}
	}
}

void TextBox::draw(RenderTarget& target)
{
	target.draw(*this);
	target.draw(text);
}
