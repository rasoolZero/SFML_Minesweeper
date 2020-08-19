#ifndef Settings_h
#define Settings_h

#include "CheckBox.h"
#include "AdjustBar.h"
#include "Screen.h"
#include "Prompt.h"
#include "SoundManager.h"
#include "Leaderboard.h"

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
	AdjustBar bars[2];

	short int soundEffectVolume = 100;
	short int musicVolume = 100;
	bool music_enabled = true;
	bool soundEffects_enabled = true;

	SoundManager & soundManager_ref;
	Leaderboard & leaderBoard_ref;

	void draw();
	void drawTitle();
	void drawSoundEffectOption();
	void drawMusicOption();
	void drawMusicVolume();
	void drawSoundEffectVolume();
	void drawResetLeaderboard();
	void drawBack();
	void drawModifiers();

	Prompt prompt;
    bool prompting=false;

    void load();
    void save();
    string fileName="settings.dat";

	void setSelectedOption(SelectedOption selectedOption);
	void setSelectedOption(short int selectedOptionIndex);
	virtual void manageInput(Keyboard::Key key);
public:

	SelectedOption getSelectedOption() { return this->selectedOption; }

	virtual void update();

	Settings(RenderWindow& window, ManagerManager& manager_ref ,SoundManager & _soundManager_ref,Leaderboard & _leaderBoard_ref);

};

#endif // !Settings_h


