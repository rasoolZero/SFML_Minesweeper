#ifndef Settings_h
#define Settings_h

#include "CheckBox.h"
#include "Screen.h"

class ManagerManager;
class Settings : public Screen
{
private:
	//SoundManager& soundManager_ref;
	enum class SelectedOption {soundToggle, soundAdjust, musicToggle, musicAdjust, leaderboardReset, back};
	SelectedOption selectedOption = SelectedOption::soundToggle;
	Text options[6];
	Texture textures[2];
	CheckBox toggles[2];

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

	SelectedOption getSelectedOption() { return this->selectedOption; }

	virtual void update();
	//void loadSettings();
	//void SaveSettings();

	Settings(RenderWindow& window, ManagerManager& manager_ref);

};

#endif // !Settings_h


