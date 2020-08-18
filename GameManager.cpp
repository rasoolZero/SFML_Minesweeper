#include "GameManager.h"
#include "ManagerManager.h"
#include <string>
using namespace std;
using namespace sf;
GameManager::GameManager(RenderWindow& window_ref, ManagerManager& manager_ref, SoundManager& soundManager_ref, Leaderboard& _leaderboard_ref)
	:Screen(window_ref, manager_ref, "fonts\\arial.ttf")
	,soundManager_ref(soundManager_ref)
	,grid{getWindow_ref(), soundManager_ref,*this}
	, customOptions{ getWindow_ref(), getFont() },
	leaderboard_ref(_leaderboard_ref)
{
	options[0].setString("easy");
	options[1].setString("medium");
	options[2].setString("hard");
	options[3].setString("custom");
	options[4].setString("back");
	short int startingPoint = getWindow_ref().getSize().y / 2 - 150;
	for (int i = 0; i < 5; i++) {
		options[i].setFont(getFont());
		if (i) {
			options[i].setFillColor(getNormalTextColor());
		}
		options[i].setCharacterSize(getNormalFontSize());
		if (i != 4) {
			options[i].setPosition(70, startingPoint + i * 65);
		}
	}
	options[0].setFillColor(getSelectedTextColor());
	options[4].setPosition(50, getWindow_ref().getSize().y - 90);
	customOptions.setGroupPosition(options[3].getPosition() + Vector2f(0, 10));

	if(!arrowTexture.loadFromFile("images/Arrow.png"))
        throw std::runtime_error("could not load arrow image");
    arrow=RectangleShape(Vector2f(40,40));
    arrow.setTexture(&arrowTexture);
    arrow.setPosition(getWindow_ref().getSize().x - arrow.getSize().x -50,6);
}

void GameManager::update()
{
	if (state == State::playing) {
		drawGame();
		checkClick();
	}
	else {
		drawDifficulty();
		if (state == State::customSelection) {
			customOptions.draw();
		}
		timerStarted=false;
		gameOver=false;
	}

}

void GameManager::drawDifficulty()
{
	for (int i = 0; i < 5; i++)
	{
		short int currentSize = options[i].getCharacterSize();
		if (i == static_cast<int>(difficulty)) {
			if (currentSize != selectedFontSize) {
				options[i].setCharacterSize(currentSize + 1);
			}
		}
		else {
			if (currentSize != getNormalFontSize()) {
				options[i].setCharacterSize(currentSize - 1);
			}
		}
		getWindow_ref().draw(options[i]);
	}

}

void GameManager::drawGame()
{
	grid.update();
	drawTimer();
	drawBombCount();
	drawRestart();
	if(gameOver){
        drawGameOver();
	}
}

void GameManager::manageInput(Keyboard::Key key)
{
	int selectedOptionIndex = static_cast<int>(this->difficulty);
	if (state == State::playing) {
		if (key == Keyboard::Escape) {
			options[selectedOptionIndex].setFillColor(getNormalTextColor());
			difficulty = Difficulty::easy;
			options[selectedOptionIndex].setCharacterSize(getNormalFontSize());
			selectedOptionIndex = 0;

			setState(State::difficultySelection);
			soundManager_ref.stopAll();
			soundManager_ref.play(SoundManager::MenuMusic);
			customOptions.reset();
			getManager_ref().setState();
		}
	}
	else if (state == State::customSelection) {
		if (key == Keyboard::Escape) {
			state = State::difficultySelection;
		}
		else if (key == Keyboard::Enter || key == Keyboard::Space) {
			grid.setupGrid(customOptions.getWidth(), customOptions.getHeight(), customOptions.getBombCount());
			setState(State::playing);
		}
		else {
			customOptions.manageInput(key);
		}
	}
	else {
		if (options[selectedOptionIndex].getCharacterSize() == selectedFontSize) {

			if (key == Keyboard::Up) {
				options[selectedOptionIndex].setFillColor(getNormalTextColor());
				setDifficulty((selectedOptionIndex += 4) %= 5); // goes to previous state in the cycle
			}
			else if (key == Keyboard::Down)
			{
				options[selectedOptionIndex].setFillColor(getNormalTextColor());
				setDifficulty((selectedOptionIndex += 1) %= 5); // goes to next state in the cycle
			}
		}
		if (key == Keyboard::Escape || ( (key == Keyboard::Enter || key == Keyboard::Space) && selectedOptionIndex == 4)) { //back
			options[selectedOptionIndex].setFillColor(getNormalTextColor());
			difficulty = Difficulty::easy;
			options[selectedOptionIndex].setCharacterSize(getNormalFontSize());
			selectedOptionIndex = 0;

			setState(State::difficultySelection);
			if (soundManager_ref.isPlaying(SoundManager::GameMusic)) {
				soundManager_ref.stopAll();
				soundManager_ref.play(SoundManager::MenuMusic);
			}
			customOptions.reset();
			getManager_ref().setState();
		}
		else if (key == Keyboard::Enter || key == Keyboard::Space) {
			if (difficulty == Difficulty::easy) {
				grid.setupGrid(9, 9);
			}
			else if (difficulty == Difficulty::medium) {
				grid.setupGrid(16, 16, 40);
			}
			else if (difficulty == Difficulty::hard) {
				grid.setupGrid(30, 16, 99);
			}
			else { //custom
				state = State::customSelection;
			}
			if (state != State::customSelection) {
				setState(State::playing);
			}
		}
	}
	options[selectedOptionIndex].setFillColor(getSelectedTextColor());
	if (state == State::playing) {
        if(!soundManager_ref.isPlaying(SoundManager::GameMusic)){
            soundManager_ref.stopAll();
            soundManager_ref.play(SoundManager::GameMusic);
        }
	}
}
void GameManager::startTimer(){
    this->timer.restart();
    timerStarted=true;
}
void GameManager::drawTimer(){
    string time="";
    if(!gameOver)
        if(timerStarted){
            Time t=timer.getElapsedTime();
            int sec=t.asSeconds();
            int min=sec/60;
            sec%=60;
            time=to_string(min)+":"+ (sec<10?"0":"") +to_string(sec);
        }
        else{
            time="0:00";
        }
    else{
        time=timeToString(score);
    }
    Text text(time,getFont(),30);
    text.setFillColor(Color::Black);
    text.setPosition(getWindow_ref().getSize().x/2 - text.getGlobalBounds().width/2,6);
    getWindow_ref().draw(text);
}


void GameManager::drawBombCount(){
    string bombs="Bombs: "+to_string(grid.getBombCount()-grid.getFlagCount());

    Text text(bombs,getFont(),30);
    text.setFillColor(Color::Black);
    text.setPosition(30,6);
    getWindow_ref().draw(text);
}
void GameManager::drawRestart(){
    getWindow_ref().draw(arrow);
}

void GameManager::checkClick(){
    if(state!=State::playing)
        return;
    static bool prevLeftButtonStatus = false;
    if(Mouse::isButtonPressed(Mouse::Left) && !prevLeftButtonStatus){

        Vector2i mousePosition=Mouse::getPosition(getWindow_ref());
        if(mousePosition.x >= arrow.getGlobalBounds().left &&
            mousePosition.x <= arrow.getGlobalBounds().left + arrow.getSize().x &&
            mousePosition.y >= arrow.getGlobalBounds().top &&
            mousePosition.y <= arrow.getGlobalBounds().top + arrow.getSize().y){
            grid.setupGrid(grid.getWidth(),grid.getHeight(),grid.getBombCount());
            timerStarted=false;
            gameOver=false;
            timer.restart();
            soundManager_ref.play(SoundManager::Reveal);
        }
    }

    prevLeftButtonStatus = Mouse::isButtonPressed(Mouse::Left);
}

void GameManager::stopTimer(){
    gameOver=true;
    score=timer.getElapsedTime();
    if(grid.getState() == Grid::Won){
        won=true;
    }
    else{
        won=false;
    }
    if(won && difficulty!=Difficulty::custom){
        hasHighScore=leaderboard_ref.isHighscore(score, static_cast<Leaderboard::Difficulties>(static_cast<int>(difficulty) ) );
    }
    else
        hasHighScore=false;
}

void GameManager::drawGameOver(){
    if(won){
        if(hasHighScore)
            drawHighScore();
        else
            drawWon();
    }
    else
        drawLost();
}
void GameManager::drawHighScore(){
    string message = "YOU WON!\nTime: "+timeToString(score)+"\nHIGHSCORE! enter your name:\n";
    Text text(message,getFont());
    text.setFillColor(Color::Black);

    FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f,
        textRect.top  + textRect.height/2.0f);
    text.setPosition(sf::Vector2f(getWindow_ref().getSize().x/2.0f,getWindow_ref().getSize().y/2.0f));

    RectangleShape background(Vector2f(text.getLocalBounds().width+20,text.getLocalBounds().height+25));
    background.setFillColor(Color(0, 199, 13,200));
    background.setOutlineColor(Color(0,0,0,200));
    background.setOutlineThickness(3);
    background.setPosition( (getWindow_ref().getSize().x/2.0 - background.getSize().x/2.0 )  , (getWindow_ref().getSize().y/2.0  - background.getSize().y/2.0 )  );
    getWindow_ref().draw(background);
    getWindow_ref().draw(text);
}
void GameManager::drawWon(){
    string message = "YOU WON!\nTime: "+timeToString(score);
    Text text(message,getFont());
    text.setFillColor(Color::Black);
    FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f,
        textRect.top  + textRect.height/2.0f);
    text.setPosition(sf::Vector2f(getWindow_ref().getSize().x/2.0f,getWindow_ref().getSize().y/2.0f));

    RectangleShape background(Vector2f(text.getLocalBounds().width+20,text.getLocalBounds().height+25));
    background.setFillColor(Color(0, 199, 13,200));
    background.setOutlineColor(Color(0,0,0,200));
    background.setOutlineThickness(3);
    background.setPosition( (getWindow_ref().getSize().x/2.0 - background.getSize().x/2.0 )  , (getWindow_ref().getSize().y/2.0  - background.getSize().y/2.0 )  );
    getWindow_ref().draw(background);
    getWindow_ref().draw(text);
}
void GameManager::drawLost(){
    string message = "YOU DIED!\nTime: "+timeToString(score);
    Text text(message,getFont());
    text.setFillColor(Color::Black);
    FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f,
        textRect.top  + textRect.height/2.0f);
    text.setPosition(sf::Vector2f(getWindow_ref().getSize().x/2.0f,getWindow_ref().getSize().y/2.0f));

    RectangleShape background(Vector2f(text.getLocalBounds().width+20,text.getLocalBounds().height+25));
    background.setFillColor(Color(199, 0, 0,200));
    background.setOutlineColor(Color(0,0,0,200));
    background.setOutlineThickness(3);
    background.setPosition( (getWindow_ref().getSize().x/2.0 - background.getSize().x/2.0 )  , (getWindow_ref().getSize().y/2.0  - background.getSize().y/2.0 )  );
    getWindow_ref().draw(background);
    getWindow_ref().draw(text);
}

string GameManager::timeToString(Time t){
    int sec=t.asSeconds();
    int min=sec/60;
    sec%=60;
    string time=to_string(min)+":"+ (sec<10?"0":"") +to_string(sec);
    return time;
}
