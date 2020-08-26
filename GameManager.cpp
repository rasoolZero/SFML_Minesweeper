#include "GameManager.h"
#include "ManagerManager.h"
#include <string>
using namespace std;
using namespace sf;
GameManager::GameManager(RenderWindow& window_ref, ManagerManager& manager_ref, SoundManager& soundManager_ref, Leaderboard& _leaderboard_ref)
	:Screen(window_ref, manager_ref, "fonts\\Roboto-Light.ttf")
	,soundManager_ref(soundManager_ref)
	,grid{getWindow_ref(), soundManager_ref,*this}
	,customOptions{ getWindow_ref(), getFont() }
	,leaderboard_ref(_leaderboard_ref)
	,highScoreName{ Vector2f(getWindow_ref().getSize().x / 2, getWindow_ref().getSize().y / 2 + 80) , getNormalFontSize(), getFont()}
{
	options[0].setString("easy");
	options[1].setString("medium");
	options[2].setString("hard");
	options[3].setString("custom");
	options[4].setString("back");
	short int startingPoint = getWindow_ref().getSize().y / 2 - 300;
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
	options[4].setPosition(150, getWindow_ref().getSize().y - 90);
	customOptions.setGroupPosition(options[3].getPosition() + Vector2f(50, 10));

	if(!arrowTexture.loadFromFile("images/Arrow.png"))
        throw std::runtime_error("could not load arrow image");
    arrowTexture.setSmooth(true);
    arrow=RectangleShape(Vector2f(40,40));
    arrow.setTexture(&arrowTexture);
    arrow.setPosition(getWindow_ref().getSize().x - arrow.getSize().x -50,6);

	result.setFont(getFont());
	result.setFillColor(Color::Black);
	result.setPosition(getWindow_ref().getSize().x / 2, getWindow_ref().getSize().y / 2);
	highScoreMessage.setFont(getFont());
	highScoreMessage.setFillColor(Color::Black);
	highScoreMessage.setPosition(getWindow_ref().getSize().x / 2, getWindow_ref().getSize().y / 2 + result.getCharacterSize());
	resultFrame.setOutlineColor(Color(0, 0, 0, 200));
	resultFrame.setOutlineThickness(3);
	resultFrame.setPosition(getWindow_ref().getSize().x / 2, getWindow_ref().getSize().y / 2 - 10);

	for (int i = 0; i < 5; i++)
	{
		optionBoxes[i].top = options[i].getGlobalBounds().top - 10;
		optionBoxes[i].left = options[i].getGlobalBounds().left - 30;
		optionBoxes[i].width = 250;
		optionBoxes[i].height = options[i].getGlobalBounds().height + 30;
	}
}

void GameManager::update()
{
	if (state == State::playing || state == State::finished) {
		drawGame();
		checkClick();
	}
	else {
		drawDifficulty();
		if (state == State::customSelection) {
			customOptions.draw();
		}
		timerStarted=false;
	}

}

void GameManager::pushChar(char input)
{
	if (hasHighScore) {
		highScoreName.manageInput(input);
	}
}

void GameManager::drawDifficulty()
{
	for (int i = 0; i < 5; i++)
	{
        /*if(i!=static_cast<int>(difficulty))
            options[i].setFillColor(getNormalTextColor());
        else
            options[i].setFillColor(getSelectedTextColor());*/
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
	if(state == State::finished){
        drawGameOver();
	}
}

void GameManager::manageInput(Keyboard::Key key)
{
	int selectedOptionIndex = static_cast<int>(this->difficulty);
	if (state == State::playing || state == State::finished) {
		if (key == Keyboard::Escape) {
			reset();
			return;
		}
		if (state == State::finished) {
			if (key == Keyboard::Enter) {
				if (hasHighScore) {
					if (highScoreName.getContent().length()) {
						leaderboard_ref.addScore(score, highScoreName.getContent().data(), static_cast<Leaderboard::Difficulties>(difficulty));
					}
					else {
						leaderboard_ref.addScore(score, "[No name]" , static_cast<Leaderboard::Difficulties>(difficulty));
					}
					reset(1);
					return;
				}
				else {
					reset();
					return;
				}
			}
		}
	}
	else if (state == State::customSelection) {
		if (key == Keyboard::Escape) {
			state = State::difficultySelection;
		}
		else if (key == Keyboard::Enter || key == Keyboard::Space) {
			startGame();
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
			reset();
			return;
		}
		else if (key == Keyboard::Enter || key == Keyboard::Space) {
			if (difficulty == Difficulty::custom) {
				state = State::customSelection;
			}
			else {
				startGame();
				return;
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
void GameManager::manageInput(Mouse::Button button, bool released)
{
	if (released) {
		return;
	}
	if (state == State::playing) {
		this->grid.manageInput(button);
		return;
	}
	if (button == Mouse::Left) {
		if (state == State::difficultySelection) {
			for (int i = 0; i < 5; i++)
			{
				if (optionBoxes[i].contains(Mouse::getPosition())) {
					if (i < 4) {
						setDifficulty(i);
						if (i == 3) { //custom
							state = State::customSelection;
						}
						else {
							startGame();
						}
						break;
					}
					else { //back
						reset();
					}
					return;
				}
			}
		}
		else if (state == State::customSelection) {
			if (customOptions.getMouseBox(0).contains(Mouse::getPosition())) {
				state = State::difficultySelection;
			}
			else if (customOptions.getMouseBox(1).contains(Mouse::getPosition())) {
				startGame();
			}
			customOptions.manageInput(button);
		}
	}
	else if (button == Mouse::Right) {
		if (state == State::customSelection) {
			state = State::difficultySelection;
		}
	}
}
void GameManager::updateMouse()
{
	if (state == State::difficultySelection) {
		int selectedOptionIndex = static_cast<int>(this->difficulty);
		options[selectedOptionIndex].setFillColor(getNormalTextColor());
		for (int i = 0; i < 5; i++)
		{
			if (optionBoxes[i].contains(Mouse::getPosition())) {
				setDifficulty(i);
				selectedOptionIndex = i;
				break;
			}
		}
		options[selectedOptionIndex].setFillColor(getSelectedTextColor());
	}
	else if (state == State::customSelection) {
		customOptions.updateMouse();
	}
}
void GameManager::startTimer(){
    this->timer.restart();
    timerStarted=true;
}
void GameManager::drawTimer(){
    string time="";
    if(state != State::finished)
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
    if(state!=State::playing && state != State::finished)
        return;
    static bool prevLeftButtonStatus = false;
    if(Mouse::isButtonPressed(Mouse::Left) && !prevLeftButtonStatus){

        Vector2i mousePosition=Mouse::getPosition(getWindow_ref());
        if( static_cast<IntRect>(arrow.getGlobalBounds()).contains(mousePosition)){
            grid.setupGrid(grid.getWidth(),grid.getHeight(),grid.getBombCount());
            timerStarted=false;
			setState(State::playing);
            timer.restart();
            soundManager_ref.play(SoundManager::Reveal);
        }
    }

    prevLeftButtonStatus = Mouse::isButtonPressed(Mouse::Left);
}

void GameManager::reset(bool isHighScore)
{
	int selectedOptionIndex = static_cast<int>(this->difficulty);
	options[selectedOptionIndex].setFillColor(getNormalTextColor());
	difficulty = Difficulty::easy;
	options[selectedOptionIndex].setCharacterSize(getNormalFontSize());
	selectedOptionIndex = 0;
	options[selectedOptionIndex].setFillColor(getSelectedTextColor());

	setState(State::difficultySelection);
	if (soundManager_ref.isPlaying(SoundManager::GameMusic)) {
		soundManager_ref.stopAll();
		soundManager_ref.play(SoundManager::MenuMusic);
	}
	customOptions.reset();
	highScoreName.reset();
	won = false;
	hasHighScore = false;
	if (isHighScore) {
		getManager_ref().setState(ManagerManager::State::leaderboard);
	}
	else {
		getManager_ref().setState();
	}
}

void GameManager::startGame()
{
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
		grid.setupGrid(customOptions.getWidth(), customOptions.getHeight(), customOptions.getBombCount());
	}
	setState(State::playing);
	if (!soundManager_ref.isPlaying(SoundManager::GameMusic)) {
		soundManager_ref.stopAll();
		soundManager_ref.play(SoundManager::GameMusic);
	}
}

void GameManager::stopTimer(){
	setState(State::finished);
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

	if (won) {
		result.setString("YOU WON!\t\tTime: " + timeToString(score));
		result.setOrigin(result.getLocalBounds().width / 2, 0);
		if (hasHighScore) {
			highScoreMessage.setString("HIGHSCORE! enter your name:");
			highScoreMessage.setOrigin(highScoreMessage.getLocalBounds().width / 2, 0);
		}
		resultFrame.setFillColor(Color(0, 199, 13, 200));
	}
	else {
		result.setString("Game Over!\t\tTime: " + timeToString(score));
		result.setOrigin(result.getLocalBounds().width / 2, 0);
		resultFrame.setFillColor(Color(199, 0, 0, 200));
	}
	short int width = result.getLocalBounds().width > highScoreMessage.getLocalBounds().width ? result.getLocalBounds().width : highScoreMessage.getLocalBounds().width;
	if (hasHighScore) {
		resultFrame.setSize(Vector2f(width + 40, result.getLocalBounds().height + highScoreMessage.getLocalBounds().height + highScoreName.getSize().y + 45));
	}
	else {
		resultFrame.setSize(Vector2f(width + 40, result.getLocalBounds().height + 45));
	}
	resultFrame.setOrigin(resultFrame.getSize().x / 2, 0);
}

void GameManager::drawGameOver(){
	getWindow_ref().draw(resultFrame);
	getWindow_ref().draw(result);
	if (hasHighScore) {
		getWindow_ref().draw(highScoreMessage);
		highScoreName.draw(getWindow_ref());
	}
}

string GameManager::timeToString(Time t){
    int sec=t.asSeconds();
    int min=sec/60;
    sec%=60;
    string time=to_string(min)+":"+ (sec<10?"0":"") +to_string(sec);
    return time;
}
