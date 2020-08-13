#ifndef Settings_h
#define Settings_h

#include "CheckBox.h"
class ManagerManager;
class Settings
{
private:
	RenderWindow& window_ref;
	ManagerManager& manager_ref;
	//SoundManager& soundManager_ref;
	enum class SelectedOption {soundToggle, soundAdjust, musicToggle, musicAdjust, leaderboardReset, back};
	SelectedOption selectedOption = SelectedOption::soundToggle;
	Text options[6];
	Texture textures[2];
	CheckBox toggles[2];
	Color normalTextColor = Color::Black;
	Color selectedTextColor = Color::Red;

	Font font;
	short int fontSize = 40;

	short int soundEffectVolume = 100;
	short int musicVolume = 100;
	bool music_enabled = true;
	bool soundEffects_enabled = true;

	void draw();
	void drawTitle();
	void drawSoundEffectOption();
	void drawMusicOption();
	void drawResetLeaderboard();
	void drawBack();
	void drawModifiers();

	void setSelectedOption(SelectedOption selectedOption);
	void setSelectedOption(short int selectedOptionIndex);
	void manageInput();
public:
	void setFontSize(short int size) { this->fontSize = size; }
	short int getFontSize() { return this->fontSize; }

	SelectedOption getSelectedOption() { return this->selectedOption; }

	void update();
	//void loadSettings();
	//void SaveSettings();

	Settings(RenderWindow& window, ManagerManager& manager_ref);

};

#endif // !Settings_h


