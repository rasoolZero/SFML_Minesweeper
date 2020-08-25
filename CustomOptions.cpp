#include "CustomOptions.h"
CustomOptions::CustomOptions(RenderWindow& window_ref, Font& font)
	:window_ref(window_ref)
{
	descriptions[0].setString("width:");
	descriptions[1].setString("height:");
	descriptions[2].setString("mine count:"); //read: bombcount

	customAmounts[0] = 16;
	customAmounts[1] = 16;
	customAmounts[2] = 40;
	for (int i = 0; i < 3; i++)
	{
		descriptions[i].setFillColor(Color(10, 10, 10));
		descriptions[i].setCharacterSize(36);
		descriptions[i].setFont(font);

		textBoxes[i].setSize(Vector2f(80, 40));
		textBoxes[i].setOrigin(40, 0);
		textBoxes[i].setFillColor(Color(150, 150, 150, 80));
		textBoxes[i].setOutlineColor(normalRectColor);
		textBoxes[i].setOutlineThickness(3);

		customTexts[i].setString(std::to_string(customAmounts[i]));
		customTexts[i].setCharacterSize(34);
		customTexts[i].setFont(font);
		customTexts[i].setOrigin(customTexts[i].getLocalBounds().width / 2, 0);
		customTexts[i].setFillColor(Color::Black);
	}
	Vector2u windowSize = window_ref.getSize();
	limits_amount[0] = limits_amount[2] = 5;
	limits_amount[4] = 1;
	limits_amount[1] = windowSize.x / 30;
	limits_amount[3] = windowSize.y / 30;
	limits_amount[5] = customAmounts[0] * customAmounts[1] - 1; // max : number of cells - 1

	for (int i = 0; i < 6; i++) {
		if (i % 2) {
			limits[i].setString("< " + std::to_string(limits_amount[i]));
		}
		else {
			limits[i].setString(std::to_string(limits_amount[i]) + " <");
		}
		limits[i].setCharacterSize(32);
		limits[i].setFont(font);
		limits[i].setFillColor(Color(25, 25, 25));
	}
	for (int i = 0; i < 2; i++)
	{
		custom_mouseBoxes[i].setFont(font);
		custom_mouseBoxes[i].setFillColor(Color::Black);
		custom_mouseBoxes[i].setCharacterSize(27);
	}
	custom_mouseBoxes[0].setString("[Esc/RMB] back");
	custom_mouseBoxes[1].setString("[Enter] start");
}

void CustomOptions::moveGroup(float x, float y)
{
	move(x, y);
	for (int i = 0; i < 3; i++)
	{
		customTexts[i].move(x, y);
		textBoxes[i].move(x, y);
		descriptions[i].move(x, y);
	}
	for (int i = 0; i < 6; i++) {
		limits[i].move(x, y);
	}
	for (int i = 0; i < 2; i++) {
		custom_mouseBoxes[i].move(x, y);
	}
}

void CustomOptions::setGroupPosition(Vector2f position)
{
	setPosition(position);
	for (int i = 0; i < 3; i++)
	{
		descriptions[i].setPosition(position.x + 50, position.y + 50 + 100 * i);
		textBoxes[i].setPosition(position.x + 165, position.y + 100 + 100 * i);
		customTexts[i].setPosition(textBoxes[i].getPosition());
	}
	for (int i = 0; i < 6; i++)
	{
		limits[i].setPosition(position.x + 60 + 170 * (i % 2), position.y + 100 + 100 * (i / 2));
	}
	for (int i = 0; i < 2; i++)
	{
		custom_mouseBoxes[i].setPosition(limits[i + 4].getPosition() + Vector2f(-40 + 30 * i, 50));
	}
}

void CustomOptions::draw()
{
	short int selectedOptionIndex = static_cast<short int>(selectedOption);
	for (int i = 0; i < 3; i++) {
		Color currentColor = textBoxes[i].getOutlineColor();
		if (i == selectedOptionIndex) {
			if (currentColor != selectedRectColor) {
				textBoxes[i].setOutlineColor(currentColor + Color(10, 0, 0, 0));
			}
		}
		else {
			if (currentColor != normalRectColor) {
				textBoxes[i].setOutlineColor(currentColor - Color(10, 0, 0, 0));
			}
		}
	}
	for (int i = 0; i < 3; i++) {
		window_ref.draw(customTexts[i]);
		window_ref.draw(textBoxes[i]);
		window_ref.draw(descriptions[i]);
	}
	for (int i = 0; i < 6; i++) {
		window_ref.draw(limits[i]);
	}
	for (int i = 0; i < 2; i++)
	{
		window_ref.draw(custom_mouseBoxes[i]);
	}
}

void CustomOptions::setSelectedOption(short int selectedOptionIndex)
{
	this->selectedOption = static_cast<SelectedOption>(selectedOptionIndex);
}

void CustomOptions::manageInput(Keyboard::Key key)
{
	short int selectedOptionIndex = static_cast<short int>(selectedOption);
	if (textBoxes[selectedOptionIndex].getOutlineColor() == selectedRectColor) {
		if (key == Keyboard::Up) {
			setSelectedOption((selectedOptionIndex + 2) % 3);
		}
		else if (key == Keyboard::Down) {
			setSelectedOption((selectedOptionIndex + 1) % 3);
		}
	}
	if (key == Keyboard::Right) {
		if (customAmounts[selectedOptionIndex] < limits_amount[selectedOptionIndex * 2 + 1]) {
			customTexts[selectedOptionIndex].setString(std::to_string(++customAmounts[selectedOptionIndex]));
			if (selectedOptionIndex != 2) {
				limits_amount[5] += customAmounts[!selectedOptionIndex];
				limits[5].setString("< " + std::to_string(limits_amount[5]));
			}
			customTexts[selectedOptionIndex].setOrigin(customTexts[selectedOptionIndex].getLocalBounds().width / 2, 0);
		}
	}
	else if (key == Keyboard::Left) {
		if (customAmounts[selectedOptionIndex] > limits_amount[selectedOptionIndex * 2]) {
			customTexts[selectedOptionIndex].setString(std::to_string(--customAmounts[selectedOptionIndex]));
			if (selectedOptionIndex != 2) {
				limits_amount[5] -= customAmounts[!selectedOptionIndex];
				limits[5].setString("< " + std::to_string(limits_amount[5]));
				if (customAmounts[2] > limits_amount[5]) {
					customAmounts[2] = limits_amount[5];
					customTexts[2].setString(std::to_string(customAmounts[2]));
				}
			}
			customTexts[selectedOptionIndex].setOrigin(customTexts[selectedOptionIndex].getLocalBounds().width / 2, 0);
		}
	}
	customTexts[selectedOptionIndex].setString(std::to_string(customAmounts[selectedOptionIndex]));
}

void CustomOptions::manageInput(Mouse::Button button)
{
	if (button == Mouse::Left) {
		for (int i = 0; i < 3; i++)
		{
			if (static_cast<IntRect>(textBoxes[i].getGlobalBounds()).contains(Mouse::getPosition())) { //if mouse is within textbox
				setSelectedOption(i);
				return;
			}
		}
	}
}

void CustomOptions::updateMouse()
{
	for (int i = 0; i < 2; i++)
	{
		if (static_cast<IntRect>(custom_mouseBoxes[i].getGlobalBounds()).contains(Mouse::getPosition())) {
			custom_mouseBoxes[i].setFillColor(Color::Red);
			return;
		}
		else {
			custom_mouseBoxes[i].setFillColor(Color::Black);
		}
	}
}

void CustomOptions::reset()
{
	setSelectedOption(0);
	customAmounts[0] = 16;
	customAmounts[1] = 16;
	customAmounts[2] = 40;
	limits_amount[5] = 255;
	limits[5].setString("< " + std::to_string(limits_amount[5]));
	for (int i = 0; i < 3; i++)
	{
		customTexts[i].setString(std::to_string(customAmounts[i]));
	}
}

IntRect CustomOptions::getMouseBox(bool index)
{
	return static_cast<IntRect>(custom_mouseBoxes[index].getGlobalBounds());
}
