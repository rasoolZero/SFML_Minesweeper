#include "Settings.h"
#include "ManagerManager.h"
#include <fstream>
#include <sstream>
using namespace sf;
using namespace std;


void Settings::update()
{
	draw();
}

Settings::Settings(RenderWindow& window, ManagerManager& manager_ref,SoundManager & _soundManager_ref,Leaderboard & _leaderBoard_ref)
	:Screen(window, manager_ref, "fonts\\Roboto-Light.ttf"),soundManager_ref(_soundManager_ref),leaderBoard_ref(_leaderBoard_ref)
	,bars {  {100,FloatRect()},{100,FloatRect()} }
	,prompt(window,getFont())
	, selectBoxes{ Color::White, Color::White, Color::White, Color::White, Color::White, Color::White }
{

	if (!textures[0].loadFromFile("images\\unchecked.png")) {
		throw std::runtime_error("unchecked texbox image could not be loaded\n");
	}
	if (!textures[1].loadFromFile("images\\checked.png")) {
		throw std::runtime_error("checked texbox image could not be loaded\n");
	}
    ifstream f(fileName);
    if(!f.good())
        save();
    else
        load();

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
        toggles[i].swtitchState();
	}

    toggles[0].setState(soundEffects_enabled);
    toggles[1].setState(music_enabled);

	bars[0] = AdjustBar( soundEffectVolume,options[1].getGlobalBounds() );
	bars[1] = AdjustBar( musicVolume,options[3].getGlobalBounds());

	for (int i = 0; i < 6; i++)
	{
		optionBoxes[i].top = options[i].getGlobalBounds().top - 10;
		optionBoxes[i].left = options[i].getGlobalBounds().left - 30;
		optionBoxes[i].height = options[i].getGlobalBounds().height + 20;
	}
	optionBoxes[0].width = optionBoxes[2].width = 360;
	optionBoxes[1].width = optionBoxes[3].width = 500;
	optionBoxes[4].width = 440;
	optionBoxes[5].width = 200;
	for (int i = 0; i < 6; i++)
	{
		selectBoxes[i].setBox(optionBoxes[i]);
		if (i) {
			selectBoxes[i].setAlpha(0);
		}
	}
	for (int i = 0; i < 2; i++)
	{
		promptOptionBoxes[i].top = prompt.getTextRect(i).top - 10;
		promptOptionBoxes[i].height = prompt.getTextRect(i).height + 20;
		promptOptionBoxes[i].width = prompt.getTextRect(-1).width / 2;
	}
	promptOptionBoxes[0].left = prompt.getTextRect(-1).left;
	promptOptionBoxes[1].left = prompt.getTextRect(-1).left + prompt.getTextRect(-1).width / 2;
}

void Settings::applyAdjust()
{
	bars[adjusting - 1].setValue_mouse();
	if (adjusting == 1) {
		soundEffectVolume = bars[adjusting - 1].getValue();
		soundManager_ref.setVolumeSoundEffects(soundEffectVolume);
	}
	else if (adjusting == 2) {
		musicVolume = bars[adjusting - 1].getValue();
		soundManager_ref.setVolumeMusics(musicVolume);
	}
}

void Settings::toggleSound()
{
	if (soundEffects_enabled) {
		soundEffects_enabled = false;
		soundManager_ref.setVolumeSoundEffects(0);
	}
	else {
		soundEffects_enabled = true;
		soundManager_ref.setVolumeSoundEffects(soundEffectVolume);
		sleep(microseconds(10));
		soundManager_ref.play(SoundManager::Reveal);
	}
	toggles[0].setState(soundEffects_enabled);
}

void Settings::toggleMusic()
{
	if (music_enabled) {
		music_enabled = false;
		soundManager_ref.setVolumeMusics(0);
		soundManager_ref.stopAll();
	}
	else {
		music_enabled = true;
		soundManager_ref.setVolumeMusics(musicVolume);
		soundManager_ref.play(SoundManager::MenuMusic);
	}
	toggles[1].setState(music_enabled);
}

void Settings::draw()
{
	drawSelected();
	drawTitle();
	drawSoundEffectOption();
	drawMusicOption();
	drawResetLeaderboard();
	drawBack();
	drawModifiers();
	if(prompting)
        getWindow_ref().draw(prompt);
}

void Settings::drawTitle()
{
	Text title;
	title.setString("settings");
	title.setCharacterSize(70);
	title.setFont(getFont());
	title.setPosition(50, 50);
	title.setFillColor(Color(180, 180, 180));
	getWindow_ref().draw(title);
}

void Settings::drawSoundEffectOption()
{
	this->getWindow_ref().draw(options[0]);

	this->getWindow_ref().draw(options[1]);
    drawSoundEffectVolume();
}
void Settings::drawSoundEffectVolume(){

    Text text(to_string(soundEffectVolume),getFont(),getNormalFontSize() - 10);
    text.setFillColor(getNormalTextColor());
	short int initial_pos = getWindow_ref().getSize().y / 2 - 160;
    text.setPosition( 600, initial_pos + 80 + 160 * (1 / 2) );
    this->getWindow_ref().draw(text);
}

void Settings::drawMusicOption()
{
	this->getWindow_ref().draw(options[2]);

	this->getWindow_ref().draw(options[3]);
    drawMusicVolume();
}
void Settings::drawMusicVolume(){

    Text text(to_string(musicVolume),getFont(),getNormalFontSize() - 10);
    text.setFillColor(getNormalTextColor());
	short int initial_pos = getWindow_ref().getSize().y / 2 - 160;
    text.setPosition( 600, initial_pos + 80 + 160 * (3 / 2) );
    this->getWindow_ref().draw(text);
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
    bars[0].setValue(soundEffectVolume);
    bars[1].setValue(musicVolume);
	Drawable* mods[4] = { &toggles[0], &toggles[1],&bars[0], &bars[1] };
	for (int i = 0; i < 4; i++)
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

void Settings::drawSelected()
{
	short int selected;
	if (getHover() != -1) {
		selected = getHover();
	}
	else {
		selected = static_cast<short int>(selectedOption);
	}
	for (int i = 0; i < 6; i++)
	{
		if (i == selected) {
			if (getHover() != -1) {
				selectBoxes[i].select(Mouse::getPosition().x);
			}
			else {
				selectBoxes[i].select();
			}
		}
		else {
			selectBoxes[i].deselect();
		}
		if (selectBoxes[i].getAlpha()) {
			getWindow_ref().draw(selectBoxes[i]);
		}
	}
}

void Settings::manageInput(Keyboard::Key key)
{
	if (adjusting) {
		return;
	}
	bool changedSettings = false;
    if(prompting){
        if(key==Keyboard::Right || key==Keyboard::Left)
            prompt.changeOption();
        if(key==Keyboard::Space || key==Keyboard::Enter){
            if(prompt.getState()){
                leaderBoard_ref.resetScores();
                soundManager_ref.play(SoundManager::Reveal);

            }
            prompting=false;
        }
        if(key==Keyboard::Escape)
            prompting=false;

        return;
    }

	int selectedOptionIndex = static_cast<int>(this->selectedOption);

	if (key == Keyboard::Up) {
		options[selectedOptionIndex].setFillColor(getNormalTextColor());
		setSelectedOption((selectedOptionIndex += 5) %= 6); // goes to previous state in the cycle
		setHover(-1);
	}
	else if (key == Keyboard::Down)
	{
		options[selectedOptionIndex].setFillColor(getNormalTextColor());
		setSelectedOption((selectedOptionIndex += 1) %= 6); // goes to next state in the cycle
		setHover(-1);
	}
	else if (key == Keyboard::Escape) {
		reset();
		return;
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
            if(soundEffects_enabled){
                soundManager_ref.setVolumeSoundEffects(soundEffectVolume);
                soundManager_ref.play(SoundManager::Reveal);
            }
			changedSettings = true;
        }
        if (selectedOption == SelectedOption::musicAdjust){
            musicVolume+=delta;
            if(musicVolume<0)
                musicVolume=0;
            else if(musicVolume>100)
                musicVolume=100;
            if(music_enabled){
                soundManager_ref.setVolumeMusics(musicVolume);
            }
			changedSettings = true;
        }
	}
	else if (key == Keyboard::Enter || key == Keyboard::Space) {
		if (selectedOption == SelectedOption::soundToggle) {
			toggleSound();
			changedSettings = true;
		}
		else if (selectedOption == SelectedOption::musicToggle) {
			toggleMusic();
			changedSettings = true;
		}
		else if (selectedOption == SelectedOption::leaderboardReset) {
            prompting=true;
		}
		else { //back
			reset();
			return;
		}
	}
	options[selectedOptionIndex].setFillColor(getSelectedTextColor());
	if (changedSettings) {
		save();
	}
}

void Settings::manageInput(Mouse::Button button, bool released)
{
	bool changedSettings = false;
	if (button == Mouse::Left) {
		if (released) {
			if (adjusting) {
				changedSettings = true;
				if (adjusting == 1) {
					soundManager_ref.play(SoundManager::Reveal);
				}
			}
			adjusting = false;
		}
		else {
			if (!prompting) {
				for (int i = 0; i < 6; i++)
				{
					if (optionBoxes[i].contains(Mouse::getPosition())) {
						if (i == 0) {
							toggleSound();
							changedSettings = true;
						}
						else if (i == 2) {
							toggleMusic();
							changedSettings = true;
						}
						else if (i == 4) {
							prompting = true;
							setHover(-1);
						}
						else if (i == 5) {
							reset();
						}
						else if (i == 1) {
							adjusting = 1;
							applyAdjust();
						}
						else if (i == 3) {
							adjusting = 2;
							applyAdjust();
						}
						break;
					}
				}
			}
			else {
				for (int i = 0; i < 2; i++)
				{
					if (promptOptionBoxes[i].contains(Mouse::getPosition())) {
						if (i) { //yes option
							leaderBoard_ref.resetScores();
							soundManager_ref.play(SoundManager::Reveal);
						}
						prompting = false;
					}
				}
			}
		}
	}
	if (changedSettings) {
		save();
	}
}

void Settings::updateMouse()
{
	if (!prompting) {
		if (adjusting) {
			applyAdjust();
		}
		else {
			int selectedOptionIndex = static_cast<int>(this->selectedOption);
			options[selectedOptionIndex].setFillColor(getNormalTextColor());
			for (int i = 0; i < 6; i++)
			{
				if (optionBoxes[i].contains(Mouse::getPosition())) {
					setSelectedOption(i);
					selectedOptionIndex = i;
					setHover(i);
					break;
				}
				setHover(-1);
			}
			options[selectedOptionIndex].setFillColor(getSelectedTextColor());
		}
	}
	else {
		for (int i = 0; i < 2; i++)
		{
			if (promptOptionBoxes[i].contains(Mouse::getPosition())) {
				prompt.setState(i);
			}
		}
	}
}

void Settings::reset()
{
	int selectedOptionIndex = static_cast<int>(this->selectedOption);
	options[selectedOptionIndex].setFillColor(getNormalTextColor());
	selectBoxes[selectedOptionIndex].setAlpha(0);
	selectedOption = SelectedOption::soundToggle;
	selectedOptionIndex = 0;
	getManager_ref().setState();
}

void Settings::load(){
    ifstream f;
    f.open(fileName, ios::in);
    f >>  soundEffects_enabled >> soundEffectVolume >> music_enabled >> musicVolume;

    soundManager_ref.setVolumeMusics(musicVolume);
    soundManager_ref.setVolumeSoundEffects(soundEffectVolume);


    if(!music_enabled){
        soundManager_ref.setVolumeMusics(0);
    }
    if(!soundEffects_enabled){
        soundManager_ref.setVolumeSoundEffects(0);
    }
    f.close();
}

void Settings::save(){
    ofstream f;
    f.open(fileName, ios::out);
    f << soundEffects_enabled << '\n' << soundEffectVolume << '\n' <<music_enabled << '\n' <<musicVolume << '\n';
    f.close();
}
