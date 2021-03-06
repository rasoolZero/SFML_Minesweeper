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
	, selectBoxes{ Color::White, Color::White, Color::White, Color::White, Color::White }
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
	if(!redArrowTexture.loadFromFile("images/RedArrow.png"))
        throw std::runtime_error("could not load red arrow image");
    arrowTexture.setSmooth(true);
    redArrowTexture.setSmooth(true);
    arrow=RectangleShape(Vector2f(40,40));

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
	for (int i = 0; i < 5; i++)
	{
		selectBoxes[i].setBox(optionBoxes[i]);
		if (i) {
			selectBoxes[i].setAlpha(0);
		}
	}
	back.setFont(getFont());
	back.setCharacterSize(30);
	back.setString("[Esc] back");
	back.setPosition( 36 ,6);
	back.setColor(Color::Black);
    arrow.setPosition( 50 + back.getGlobalBounds().width ,6);
    arrow.setTexture(&arrowTexture);
}

void GameManager::update()
{
	if (state == State::playing || state == State::finished) {
		drawGame();
		checkClick();
	}
	else {
		drawSelected();
		drawDifficulty();
		if (state == State::customSelection) {
			customOptions.draw();
		}
		timerStarted=false;
	}

}

void GameManager::pushChar(char input)
{
	if (state == State::customSelection) {
		customOptions.pushChar(input);
	}
	else if (hasHighScore) {
		highScoreName.manageInput(input);
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
	drawBack();
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
				setHover(-1);
			}
			else if (key == Keyboard::Down)
			{
				options[selectedOptionIndex].setFillColor(getNormalTextColor());
				setDifficulty((selectedOptionIndex += 1) %= 5); // goes to next state in the cycle
				setHover(-1);
			}
		}
		if (key == Keyboard::Escape || ( (key == Keyboard::Enter || key == Keyboard::Space) && selectedOptionIndex == 4)) { //back
			reset();
			return;
		}
		else if (key == Keyboard::Enter || key == Keyboard::Space) {
			if (difficulty == Difficulty::custom) {
				setHover(-1);
				state = State::customSelection;
				updateMouse();
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
    if ( state == State::finished || state == State::playing){
		if(button == Mouse::Left)
            if( static_cast<IntRect>(back.getGlobalBounds()).contains(Mouse::getPosition(getWindow_ref()) )){
                reset();
                return;
            }
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
							setHover(-1);
							updateMouse();
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
				setHover(i);
				break;
			}
			setHover(-1);
		}
		options[selectedOptionIndex].setFillColor(getSelectedTextColor());
	}
	else if (state == State::customSelection) {
		customOptions.updateMouse();
	}
    else if (state == State::playing || state == State::finished){

        if( static_cast<IntRect>(back.getGlobalBounds()).contains(Mouse::getPosition(getWindow_ref()) ))
            back.setFillColor(getSelectedTextColor());
        else
            back.setFillColor(Color::Black);


        if( static_cast<IntRect>(arrow.getGlobalBounds()).contains(Mouse::getPosition(getWindow_ref()) ))
            arrow.setTexture(&redArrowTexture);
        else
            arrow.setTexture(&arrowTexture);
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
    text.setPosition( getWindow_ref().getSize().x - 36 - text.getGlobalBounds().width ,6);
    getWindow_ref().draw(text);
}
void GameManager::drawBack(){
    getWindow_ref().draw(back);
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
	selectBoxes[selectedOptionIndex].setAlpha(0);
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
	updateMouse();
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

void GameManager::drawSelected()
{
	short int selected;
	if (getHover() != -1) {
		selected = getHover();
	}
	else {
		selected = static_cast<short int>(difficulty);
	}
	for (int i = 0; i < 5; i++)
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
