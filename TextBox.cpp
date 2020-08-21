#include "TextBox.h"

TextBox::TextBox(Vector2f position, short int  fontSize, Font& font, short int limit)
	:charLimit(limit)
	,fontSize(fontSize)
{
	text.setFont(font);
	text.setFillColor(Color::Black);
	setOrigin(40, 0);
	setSize(Vector2f(80, fontSize + 6));
	setPosition(position);
	setOutlineColor(Color::Black);
	setOutlineThickness(1);
	setFillColor(Color(200, 200, 200, 200));

}

void TextBox::manageInput(char key)
{
	bool changed = 0;
	if (key == '\b') {
		if (content.length()) {
			content.pop_back();
		}
		changed = 1;
	}
	else if ( (content.length() < charLimit) && (isalnum(key) || key == '_' || key == ' ') ) {
		content += key;
		changed = 1;
	}
	if (changed) {
		text.setString(content);
		short int width = text.getLocalBounds().width;
		text.setOrigin(width / 2, 0);
		text.setPosition(this->getPosition());
		if (getSize().x - width < 20) {
			setSize(Vector2f(width + 20, fontSize + 6));
			setOrigin(getSize().x / 2, 0);
		}
		else if (getSize().x - width > 80) {
			setSize(Vector2f(width > 60 ? width + 20 : 80, fontSize + 6));
			setOrigin(getSize().x / 2, 0);
		}
	}
}

void TextBox::draw(RenderTarget& target)
{
	target.draw(*this);
	target.draw(text);
}

void TextBox::reset()
{
	setSize(Vector2f(80, fontSize + 6));
	setOrigin(40, 0);
	content.clear();
	text.setString(content);
	text.setOrigin(getLocalBounds().width / 2, 0);
}
