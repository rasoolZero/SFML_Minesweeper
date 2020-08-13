#include "Settings.h"
#include "ManagerManager.h"


void Settings::update()
{
	draw();
	
	manageInput();
}

Settings::Settings(RenderWindow& window, ManagerManager& manager_ref)
	:window_ref(window)
	,manager_ref(manager_ref)
{
	if (!font.loadFromFile("fonts\\arial.ttf")) {
		throw std::runtime_error("default font could not be loaded\n");
	}
	if (!textures[0].loadFromFile("images\\unchecked.png")) {
		throw std::runtime_error("uncheckedd texbox image could not be loaded\n");
	}
	if (!textures[1].loadFromFile("images\\checked.png")) {
		throw std::runtime_error("checkedd texbox image could not be loaded\n");
	}
	
	options[0].setString("sound effects");
	options[1].setString("volume");
	options[2].setString("music");
	options[3].setString("volume");
	options[4].setString("reset leaderboards");
	options[5].setString("back");

	short int initial_pos = window_ref.getSize().y / 2 - 160;
	for (int i = 0; i < 6; i++)
	{
		options[i].setFont(font);
		options[i].setFillColor(normalTextColor);
		if (i == 1 || i == 3) {
			options[i].setCharacterSize(fontSize - 10);
			options[i].setPosition(220, initial_pos + 80 + 160 * (i / 2));
		}
		else{
			options[i].setCharacterSize(fontSize);
			if (i == 5) {
				options[i].setPosition(70, window_ref.getSize().y - 90);
			}
			else {
				options[i].setPosition(180, initial_pos + 160 * (i / 2));
			}
		}
		
	}
	for (int i = 0; i < 2; i++)
	{
		FloatRect endOfText = options[2 * i].getGlobalBounds();
	toggles[i] = CheckBox(32, Vector2f(endOfText.left + endOfText.width + 30, endOfText.top + 3), textures[0], textures[1]);
	toggles[i].setTexture(&textures[0]);
	}
}

void Settings::draw()
{	
	
	drawTitle();
	drawSoundEffectOption();
	drawMusicOption();
	drawResetLeaderboard();
	drawBack();
	drawModifiers();
}

void Settings::drawTitle()
{
	Text title;
	title.setString("settings");
	title.setCharacterSize(70);
	title.setFont(font);
	title.setPosition(50, 50);
	title.setFillColor(Color(120, 120, 120));
	window_ref.draw(title);
}

void Settings::drawSoundEffectOption()
{
	this->window_ref.draw(options[0]);

	this->window_ref.draw(options[1]);
}

void Settings::drawMusicOption()
{
	this->window_ref.draw(options[2]);

	this->window_ref.draw(options[3]);
}

void Settings::drawResetLeaderboard()
{
	this->window_ref.draw(options[4]);
}

void Settings::drawBack()
{
	this->window_ref.draw(options[5]);
}

void Settings::drawModifiers()
{
	Drawable* mods[4] = { &toggles[0], &toggles[1] };
	for (int i = 0; i < 2; i++)
	{
		window_ref.draw(*mods[i]);
	}
}

void Settings::setSelectedOption(SelectedOption selectedOption)
{
	this->selectedOption = selectedOption;
}

void Settings::setSelectedOption(short int selectedOptionIndex)
{
	this->selectedOption = static_cast<SelectedOption>(selectedOptionIndex);
}

void Settings::manageInput()
{
	static bool prevUpKeyStatus = false;
	static bool prevDownKeyStatus = false;
	static bool prevToggleKeyStatus = false; //for Enter and Space keys
	int selectedOptionIndex = static_cast<int>(this->selectedOption);

	if (Keyboard::isKeyPressed(Keyboard::Up) && !prevUpKeyStatus) {
		options[selectedOptionIndex].setFillColor(normalTextColor);
		setSelectedOption((selectedOptionIndex += 5) %= 6); // goes to previous state in the cycle
	}
	else if (Keyboard::isKeyPressed(Keyboard::Down) && !prevDownKeyStatus)
	{
		options[selectedOptionIndex].setFillColor(normalTextColor);
		setSelectedOption((selectedOptionIndex += 1) %= 6); // goes to next state in the cycle
	}
	if ((Keyboard::isKeyPressed(Keyboard::Enter) || Keyboard::isKeyPressed(Keyboard::Space)) && !prevToggleKeyStatus) {
		if (selectedOption == SelectedOption::soundToggle) {
			toggles[0].swtitchState();
			//toggle sound
			//play sound feedback
		}
		else if (selectedOption == SelectedOption::musicToggle) {
			toggles[1].swtitchState();
			//toggle music
			//play sound feedback
		}
		else if (selectedOption == SelectedOption::leaderboardReset) {
			// reset leaderboard
			//sound feedback
		}
		else { //back

 			options[selectedOptionIndex].setFillColor(normalTextColor);
			selectedOption = SelectedOption::soundToggle;
			selectedOptionIndex = 0;
			manager_ref.setState();
		}
	}
	options[selectedOptionIndex].setFillColor(selectedTextColor);

	prevUpKeyStatus = Keyboard::isKeyPressed(Keyboard::Up);
	prevDownKeyStatus = Keyboard::isKeyPressed(Keyboard::Down);
	prevToggleKeyStatus = Keyboard::isKeyPressed(Keyboard::Enter) | Keyboard::isKeyPressed(Keyboard::Space);
}
