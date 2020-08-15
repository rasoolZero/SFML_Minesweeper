#include "Settings.h"
#include "ManagerManager.h"
using namespace sf;


void Settings::update()
{
	draw();

	//manageInput();
}

Settings::Settings(RenderWindow& window, ManagerManager& manager_ref,SoundManager & _soundManager_ref)
	:Screen(window, manager_ref, "fonts\\arial.ttf"),soundManager_ref(_soundManager_ref)
{

	if (!textures[0].loadFromFile("images\\unchecked.png")) {
		throw std::runtime_error("unchecked texbox image could not be loaded\n");
	}
	if (!textures[1].loadFromFile("images\\checked.png")) {
		throw std::runtime_error("checked texbox image could not be loaded\n");
	}

	options[0].setString("sound effects");
	options[1].setString("volume");
	options[2].setString("music");
	options[3].setString("volume");
	options[4].setString("reset leaderboards");
	options[5].setString("back");

	short int initial_pos = getWindow_ref().getSize().y / 2 - 160;
	for (int i = 0; i < 6; i++)
	{
		options[i].setFont(getFont());
		if (i) {
			options[i].setFillColor(getNormalTextColor());
		}
		if (i == 1 || i == 3) {
			options[i].setCharacterSize(getNormalFontSize() - 10);
			options[i].setPosition(220, initial_pos + 80 + 160 * (i / 2));
		}
		else{
			options[i].setCharacterSize(getNormalFontSize());
			if (i == 5) {
				options[i].setPosition(70, getWindow_ref().getSize().y - 90);
			}
			else {
				options[i].setPosition(180, initial_pos + 160 * (i / 2));
			}
		}
	}
	options[0].setFillColor(getSelectedTextColor());
	for (int i = 0; i < 2; i++)
	{
		FloatRect endOfText = options[2 * i].getGlobalBounds();
	toggles[i] = CheckBox(32, Vector2f(endOfText.left + endOfText.width + 30, endOfText.top + 3), textures[0], textures[1]);
	toggles[i].setTexture(&textures[1]);
	toggles[i].swtitchState();
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
	title.setFont(getFont());
	title.setPosition(50, 50);
	title.setFillColor(Color(120, 120, 120));
	getWindow_ref().draw(title);
}

void Settings::drawSoundEffectOption()
{
	this->getWindow_ref().draw(options[0]);

	this->getWindow_ref().draw(options[1]);
    drawSoundEffectBar();
}

void Settings::drawSoundEffectBar(){
    RectangleShape shape(Vector2f ( 200 ,options[1].getGlobalBounds().height ) );
    shape.setPosition( options[1].getGlobalBounds().left + options[1].getGlobalBounds().width + 40  , options[1].getGlobalBounds().top );
    shape.setFillColor(Color::Transparent);
    shape.setOutlineThickness(2);
    shape.setOutlineColor(Color::Black);
    this->getWindow_ref().draw(shape);
    shape.setSize(Vector2f (soundEffectVolume * 2  ,options[1].getGlobalBounds().height ) );
    shape.setFillColor(Color::Red);
    shape.setOutlineThickness(0);
    this->getWindow_ref().draw(shape);
}

void Settings::drawMusicOption()
{
	this->getWindow_ref().draw(options[2]);

	this->getWindow_ref().draw(options[3]);
	drawMusicBar();
}

void Settings::drawMusicBar(){

    RectangleShape shape(Vector2f ( 200 ,options[3].getGlobalBounds().height ) );
    shape.setPosition( options[3].getGlobalBounds().left + options[3].getGlobalBounds().width + 40  , options[3].getGlobalBounds().top );
    shape.setFillColor(Color::Transparent);
    shape.setOutlineThickness(2);
    shape.setOutlineColor(Color::Black);
    this->getWindow_ref().draw(shape);
    shape.setSize(Vector2f (musicVolume * 2  ,options[3].getGlobalBounds().height ) );
    shape.setFillColor(Color::Red);
    shape.setOutlineThickness(0);
    this->getWindow_ref().draw(shape);
}

void Settings::drawResetLeaderboard()
{
	this->getWindow_ref().draw(options[4]);
}

void Settings::drawBack()
{
	this->getWindow_ref().draw(options[5]);
}

void Settings::drawModifiers()
{
	Drawable* mods[4] = { &toggles[0], &toggles[1] };
	for (int i = 0; i < 2; i++)
	{
		getWindow_ref().draw(*mods[i]);
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

void Settings::manageInput(Keyboard::Key key)
{
	int selectedOptionIndex = static_cast<int>(this->selectedOption);

	if (key == Keyboard::Up) {
		options[selectedOptionIndex].setFillColor(getNormalTextColor());
		setSelectedOption((selectedOptionIndex += 5) %= 6); // goes to previous state in the cycle
	}
	else if (key == Keyboard::Down)
	{
		options[selectedOptionIndex].setFillColor(getNormalTextColor());
		setSelectedOption((selectedOptionIndex += 1) %= 6); // goes to next state in the cycle
	}
	else if (key == Keyboard::Escape) {
		options[selectedOptionIndex].setFillColor(getNormalTextColor());
		selectedOption = SelectedOption::soundToggle;
		selectedOptionIndex = 0;
		getManager_ref().setState();
	}
	else if(key == Keyboard::Left || key == Keyboard::Right ){
	    short int delta;
        if(key == Keyboard::Left)
            delta=-5;
        else
            delta=5;
        if (selectedOption == SelectedOption::soundAdjust){
            soundEffectVolume+=delta;
            if(soundEffectVolume<0)
                soundEffectVolume=0;
            else if(soundEffectVolume>100)
                soundEffectVolume=100;
            soundManager_ref.setVolumeSoundEffects(soundEffectVolume);
            soundManager_ref.play(SoundManager::Reveal);
        }
        if (selectedOption == SelectedOption::musicAdjust){
            musicVolume+=delta;
            if(musicVolume<0)
                musicVolume=0;
            else if(musicVolume>100)
                musicVolume=100;
            soundManager_ref.setVolumeMusics(musicVolume);
        }
	}
	else if (key == Keyboard::Enter || key == Keyboard::Space) {
		if (selectedOption == SelectedOption::soundToggle) {
			toggles[0].swtitchState();
			if(soundEffects_enabled){
                soundEffects_enabled=false;
                soundManager_ref.setVolumeSoundEffects(0);
			}
			else{
                soundEffects_enabled=true;
                soundManager_ref.setVolumeSoundEffects(soundEffectVolume);
                soundManager_ref.play(SoundManager::Reveal);
			}
		}
		else if (selectedOption == SelectedOption::musicToggle) {
			toggles[1].swtitchState();
			if(music_enabled){
                music_enabled=false;
                soundManager_ref.setVolumeMusics(0);
                soundManager_ref.stopAll();
			}
			else{
                music_enabled=true;
                soundManager_ref.setVolumeMusics(musicVolume);
                soundManager_ref.play(SoundManager::MenuMusic);
			}
		}
		else if (selectedOption == SelectedOption::leaderboardReset) {
			// reset leaderboard
			//sound feedback
		}
		else { //back

 			options[selectedOptionIndex].setFillColor(getNormalTextColor());
			selectedOption = SelectedOption::soundToggle;
			selectedOptionIndex = 0;
			getManager_ref().setState();
		}
	}
	options[selectedOptionIndex].setFillColor(getSelectedTextColor());
}
