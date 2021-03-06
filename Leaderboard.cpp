#include "Leaderboard.h"
#include <fstream>
#include <string>
#include <cstring>
#include "ManagerManager.h"
using namespace std;
using namespace sf;

Leaderboard::Leaderboard(RenderWindow& _window_ref, ManagerManager& manager_ref)
    : Screen(_window_ref, manager_ref, "fonts\\Roboto-Light.ttf", 24)
    , selectBoxes{ Color::White, Color::White, Color::White}
{

    ifstream f(fileName);
    if(!f.good())
        init();
    else
        load();


	if (!font.loadFromFile("fonts\\Roboto-Light.ttf")) {
		throw std::runtime_error("menu font could not be loaded\n");
	}
	options[0].setString("Easy highscores");
	options[1].setString("Normal highscores");
	options[2].setString("Hard highscores");
	for (int i = 0; i < 4; i++) {
		options[i].setFont(font);
        if (i) {
		options[i].setFillColor(getNormalTextColor());
        }
		options[i].setCharacterSize(getNormalFontSize());
        if (i == 3) {
            continue;
        }
		options[i].setPosition( (getWindow_ref().getSize().x/6*(i*2+1)) - options[i].getGlobalBounds().width/2 , 24);
	}
    options[0].setFillColor(getSelectedTextColor());

    options[3].setString("[Esc] back");
    options[3].setPosition(5, getWindow_ref().getSize().y - 40);

    for (int i = 0; i < 4; i++)
    {
        optionBoxes[i].top = options[i].getGlobalBounds().top - 10;
        optionBoxes[i].height = options[i].getGlobalBounds().height + 20;
        if (i == 3) {
            continue;
        }
        optionBoxes[i].left = i * getWindow_ref().getSize().x / 3;
        optionBoxes[i].width = getWindow_ref().getSize().x / 3;
    }
    optionBoxes[3].width = 150;
    optionBoxes[3].top = options[3].getGlobalBounds().top - 10;
    for (int i = 0; i < 3; i++)
    {
        selectBoxes[i].setBox(optionBoxes[i], true);
        if (i) {
            selectBoxes[i].setAlpha(0);
        }
    }
}
void Leaderboard::init(){
    for(int j=0;j<3;j++)
        for(int i=0;i<10;i++){
            Record sample={"---",milliseconds(0)};
            highScores[j][i]=sample;
        }
    save();
}
void Leaderboard::load(){
    ifstream f;
    f.open(fileName,ios::binary | ios::in);
    f.read( (char *)&highScores ,30*sizeof(Record));
    f.close();
}

void Leaderboard::save(){
    ofstream f;
    f.open(fileName,ios::binary | ios::out);
    f.write( (char *)&highScores ,30*sizeof(Record));
    f.close();
}

void Leaderboard::reset()
{
    int selectedOptionIndex = static_cast<int>(this->selectedOption);
    options[selectedOptionIndex].setFillColor(getNormalTextColor());
    selectBoxes[selectedOptionIndex].setAlpha(0);
    selectedOption = Difficulties::Easy;
    selectedOptionIndex = 0;
    options[selectedOptionIndex].setFillColor(getSelectedTextColor());
    options[selectedOptionIndex].setCharacterSize(getNormalFontSize());
    options[3].setFillColor(getNormalTextColor());
    getManager_ref().setState();
}

bool Leaderboard::isHighscore(Time time,Difficulties difficulty){
    for(int i=0;i<10;i++){
        if( time<highScores[(int)difficulty][i].score || highScores[(int)difficulty][i].score.asMilliseconds()==0 ){
            return true;
        }
    }
    return false;
}
void Leaderboard::addScore(Time time,const char name[16],Difficulties difficulty){
    int diffIndex=static_cast<int>(difficulty);
    int index=-1;
    for(int i=0;i<10;i++){
        if( time<highScores[diffIndex][i].score || highScores[diffIndex][i].score.asMilliseconds()==0 ){
            index=i;
            break;
        }
    }
    if(index!=-1){
        for(int j=8;j>=index;j--){
            highScores[diffIndex][j+1]=highScores[diffIndex][j];
        }
        Record newScore={"",time};
        strncpy(newScore.name,name, 16);
        highScores[diffIndex][index]=newScore;
    }
    save();
    options[static_cast<int>(selectedOption)].setFillColor(getNormalTextColor());
    setSelectedOption(difficulty);
    options[static_cast<int>(selectedOption)].setFillColor(getSelectedTextColor());
}

void Leaderboard::update(){
    draw();
}

void Leaderboard::draw(){
	for (int i = 0; i < 3; i++)
	{
		short int currentSize = options[i].getCharacterSize();
		if (i == static_cast<int>(selectedOption)) {
			if (currentSize != selectedFontSize) {
				options[i].setCharacterSize(currentSize + 1);
			}
		}
		else {
			if (currentSize != getNormalFontSize()) {
				options[i].setCharacterSize(currentSize - 1);
			}
		}
	}
    drawSelected();
    drawOptions();
    drawScores();
}

void Leaderboard::manageInput(Keyboard::Key key) {
	int selectedOptionIndex = static_cast<int>(this->selectedOption);
	if (options[selectedOptionIndex].getCharacterSize() == selectedFontSize) {

		if (key == Keyboard::Left) {
			options[selectedOptionIndex].setFillColor(getNormalTextColor());
			setSelectedOption( (selectedOptionIndex += 2) %= 3 ); // goes to previous state in the cycle
            setHover(-1);
		}
		else if (key == Keyboard::Right)
		{
			options[selectedOptionIndex].setFillColor(getNormalTextColor());
			setSelectedOption( (selectedOptionIndex += 1) %= 3 ); // goes to next state in the cycle
            setHover(-1);
		}
        else if (key == Keyboard::Escape) {
            reset();
            return;
        }
		options[selectedOptionIndex].setFillColor(getSelectedTextColor());
	}
}

void Leaderboard::manageInput(Mouse::Button button, bool released)
{
    if (released) {
        return;
    }
    if (button == Mouse::Left) {
        if (optionBoxes[3].contains(Mouse::getPosition())) {
            reset();
        }
    }
}

void Leaderboard::updateMouse()
{
    int selectedOptionIndex = static_cast<int>(this->selectedOption);
    options[selectedOptionIndex].setFillColor(getNormalTextColor());
    for (int i = 0; i < 3; i++)
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
    if (optionBoxes[3].contains(Mouse::getPosition())) {
        options[3].setFillColor(getSelectedTextColor());
    }
    else {
        options[3].setFillColor(getNormalTextColor());
    }
}

void Leaderboard::drawOptions(){
    for(int i=0;i<4;i++){
        getWindow_ref().draw(options[i]);
    }
}

void Leaderboard::drawSelected()
{
    short int selected;
    if (getHover() != -1) {
        selected = getHover();
    }
    else {
        selected = static_cast<short int>(selectedOption);
    }
    for (int i = 0; i < 3; i++)
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

void Leaderboard::drawScores(){
    int diffIndex=static_cast<int>(selectedOption);
    Text text;
    text.setFillColor(getNormalTextColor());
    text.setFont(font);
    text.setCharacterSize(getNormalFontSize());
    for(int i=0;i<10;i++){
        text.setString(highScores[diffIndex][i].name);
        text.setPosition(getWindow_ref().getSize().x/4 , 100 + ((getWindow_ref().getSize().y-100)/10*i));
        getWindow_ref().draw(text);
    }

    for(int i=0;i<10;i++){
        int seconds = highScores[diffIndex][i].score.asSeconds();
        int minutes = seconds/60;
        seconds%=60;
        text.setString( to_string(minutes ) + ":"+ (seconds<10?"0":"") +to_string(seconds));
        text.setPosition(getWindow_ref().getSize().x/4*3 , 100 + ((getWindow_ref().getSize().y-100)/10*i));
        getWindow_ref().draw(text);
    }
}

void Leaderboard::setSelectedOption(Difficulties selectedOption)
{
	this->selectedOption = selectedOption;

}
void Leaderboard::setSelectedOption(short int selectedOptionIndex)
{
	this->selectedOption = static_cast<Difficulties>(selectedOptionIndex);

}

void Leaderboard::resetScores(){
    init();
}
