#include "Leaderboard.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "ManagerManager.h"
using namespace std;
using namespace sf;

Leaderboard::Leaderboard(RenderWindow & _window_ref, ManagerManager& manager_ref)
    : window_ref(_window_ref)
    ,manager_ref(manager_ref)
{

    ifstream f(fileName);
    if(!f.good())
        init();
    else
        load();


	if (!font.loadFromFile("fonts\\arial.ttf")) {
		throw std::runtime_error("menu font could not be loaded\n");
	}
	options[0].setString("Easy highscores");
	options[1].setString("Normal highscores");
	options[2].setString("Hard highscores");
	for (int i = 0; i < 3; i++) {
		options[i].setFont(font);
		options[i].setFillColor(normalTextColor);
		options[i].setCharacterSize(normalFontSize);
		options[i].setPosition( (window_ref.getSize().x/6*(i*2+1)) - options[i].getGlobalBounds().width/2 , 24);
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

bool Leaderboard::isHighscore(Time time,Difficulties difficulty){
    for(int i=0;i<10;i++){
        if( time<highScores[(int)difficulty][i].score || highScores[(int)difficulty][i].score.asMilliseconds()==0 ){
            return true;
        }
    }
    return false;
}
void Leaderboard::addScore(Time time,char name[16],Difficulties difficulty){
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
}

void Leaderboard::update(){
    checkInput();
    draw();
}

void Leaderboard::draw(){
    window_ref.clear(Color(235,235,250));

	for (int i = 0; i < 3; i++)
	{
		short int currentSize = options[i].getCharacterSize();
		if (i == static_cast<int>(selectedOption)) {
			if (currentSize != selectedFontSize) {
				options[i].setCharacterSize(currentSize + 1);
			}
		}
		else {
			if (currentSize != normalFontSize) {
				options[i].setCharacterSize(currentSize - 1);
			}
		}
	}

    drawOptions();
    drawScores();
    drawBack();
}

void Leaderboard::checkInput(){
    static bool prevLeftKeyStatus = false;
    static bool prevRightKeyStatus = false;
	int selectedOptionIndex = static_cast<int>(this->selectedOption);
	if (options[selectedOptionIndex].getCharacterSize() == selectedFontSize) {

		if (Keyboard::isKeyPressed(Keyboard::Left) && !prevLeftKeyStatus) {
			options[selectedOptionIndex].setFillColor(normalTextColor);
			setSelectedOption( (selectedOptionIndex += 2) %= 3 ); // goes to previous state in the cycle
		}
		else if (Keyboard::isKeyPressed(Keyboard::Right) && !prevRightKeyStatus )
		{
			options[selectedOptionIndex].setFillColor(normalTextColor);
			setSelectedOption( (selectedOptionIndex += 1) %= 3 ); // goes to next state in the cycle
		}
		options[selectedOptionIndex].setFillColor(selectedTextColor);
	}

    prevLeftKeyStatus=Keyboard::isKeyPressed(Keyboard::Left);
    prevRightKeyStatus=Keyboard::isKeyPressed(Keyboard::Right);

}

void Leaderboard::drawOptions(){
    for(int i=0;i<3;i++){
        window_ref.draw(options[i]);
    }
}

void Leaderboard::drawScores(){
    int diffIndex=static_cast<int>(selectedOption);
    Text text;
    text.setFillColor(Color::Black);
    text.setFont(font);
    text.setCharacterSize(normalFontSize);
    for(int i=0;i<10;i++){
        text.setString(highScores[diffIndex][i].name);
        text.setPosition(window_ref.getSize().x/4 , 100 + ((window_ref.getSize().y-100)/10*i));
        window_ref.draw(text);
    }

    for(int i=0;i<10;i++){
        int seconds = highScores[diffIndex][i].score.asSeconds();
        int minutes = seconds/60;
        seconds%=60;
        text.setString( to_string(minutes ) + ":"+to_string(seconds));
        text.setPosition(window_ref.getSize().x/4*3 , 100 + ((window_ref.getSize().y-100)/10*i));
        window_ref.draw(text);
    }
}
void Leaderboard::drawBack(){
    Text text;
    text.setFillColor(Color::Black);
    text.setFont(font);
    text.setCharacterSize(normalFontSize);
    text.setString("[Esc] back");
    text.setPosition(5,window_ref.getSize().y-40);
    window_ref.draw(text);
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
