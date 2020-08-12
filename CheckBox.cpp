#include "CheckBox.h"

void CheckBox::setState(bool state)
{
	if (this->state != state) {
		if (state) {
			this->setTexture(&this->checked);
		}
		else {
			this->setTexture(&this->unchecked);
		}
		this->state = state;
	}
}

CheckBox::CheckBox(short int length, Vector2f position, Texture& unchecked, Texture& checked)
	:checked(checked)
	,unchecked(unchecked)
{
	setSize(Vector2f(length, length));
	setPosition(position);
}
