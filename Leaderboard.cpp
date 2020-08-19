#include "Leaderboard.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "ManagerManager.h"
using namespace std;
using namespace sf;

Leaderboard::Leaderboard(RenderWindow& _window_ref, ManagerManager& manager_ref)
    : Screen(_window_ref, manager_ref, "fonts\\Roboto-Light.ttf", 24)
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
	for (int i = 0; i < 3; i++) {
		options[i].setFont(font);
        if (i) {
		options[i].setFillColor(getNormalTextColor());
        }
		options[i].setCharacterSize(getNormalFontSize());
		options[i].setPosition( (getWindow_ref().getSize().x/6*(i*2+1)) - options[i].getGlobalBounds().width/2 , 24);
	}
    options[0].setFillColor(getSelectedTextColor());
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
    cout << index <<endl;
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
    //checkInput();
    draw();
}

void Leaderboard::draw(){
    getWindow_ref().clear(Color(235,235,250));

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

    drawOptions();
    drawScores();
    drawBack();
}

void Leaderboard::manageInput(Keyboard::Key key) {
	int selectedOptionIndex = static_cast<int>(this->selectedOption);
	if (options[selectedOptionIndex].getCharacterSize() == selectedFontSize) {

		if (key == Keyboard::Left) {
			options[selectedOptionIndex].setFillColor(getNormalTextColor());
			setSelectedOption( (selectedOptionIndex += 2) %= 3 ); // goes to previous state in the cycle
		}
		else if (key == Keyboard::Right)
		{
			options[selectedOptionIndex].setFillColor(getNormalTextColor());
			setSelectedOption( (selectedOptionIndex += 1) %= 3 ); // goes to next state in the cycle
		}
        else if (key == Keyboard::Escape) {
            options[selectedOptionIndex].setFillColor(getNormalTextColor());
            selectedOption = Difficulties::Easy;
            selectedOptionIndex = 0;
            getManager_ref().setState();
        }
		options[selectedOptionIndex].setFillColor(getSelectedTextColor());
	}
}

void Leaderboard::drawOptions(){
    for(int i=0;i<3;i++){
        getWindow_ref().draw(options[i]);
    }
}

void Leaderboard::drawScores(){
    int diffIndex=static_cast<int>(selectedOption);
    Text text;
    text.setFillColor(Color::Black);
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
        text.setString( to_string(minutes ) + ":"+to_string(seconds));
        text.setPosition(getWindow_ref().getSize().x/4*3 , 100 + ((getWindow_ref().getSize().y-100)/10*i));
        getWindow_ref().draw(text);
    }
}
void Leaderboard::drawBack(){
    Text text;
    text.setFillColor(Color::Black);
    text.setFont(font);
    text.setCharacterSize(getNormalFontSize());
    text.setString("[Esc] back");
    text.setPosition(5,getWindow_ref().getSize().y-40);
    getWindow_ref().draw(text);
}

void Leaderboard::setSelectedOption(Difficulties selectedOption)
{
	this->selectedOption = selectedOption;

}
void Leaderboard::setSelectedOption(short int selectedOptionIndex)
{
	this->selectedOption = static_cast<Difficulties>(selectedOptionIndex);

}

void Leaderboard::reset(){
    init();
}
