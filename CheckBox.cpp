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

void CheckBox::swtitchState()
{
	this->state = !this->state;
	if (state) {
		this->setTexture(&this->checked);
	}
	else {
		this->setTexture(&this->unchecked);
	}
}

CheckBox::CheckBox(short int length, Vector2f position, Texture& unchecked, Texture& checked)
	:checked(checked)
	,unchecked(unchecked)
	,RectangleShape(Vector2f(length, length))
{	
	this->setTexture(&this->unchecked);
	setPosition(position);
}

CheckBox::CheckBox()
{	
	this->setTexture(&this->unchecked);
	//default ctor
}
