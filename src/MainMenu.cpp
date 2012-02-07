#include "MainMenu.hpp"

using namespace std;

MainMenu::MainMenu(sf::RenderWindow& renderWindow) :
	renderWindow(renderWindow),
	gameStarted(false),
	initialized(false)
{
	texBackground = Game::textureManager.Acquire(thor::Resources::TextureKey::FromFile("res/menuBackground.png"));
	init();
}

void MainMenu::init() {
	if(!initialized) {
		background.SetTexture(*texBackground);
		background.SetPosition(0.0f,0.0f);

		buttons.push_back(Button(sf::Vector2f(340.0f,400.0f),"New Game",boost::bind(&MainMenu::callbackNewGame,this)));
		buttons.push_back(Button(sf::Vector2f(340.0f,500.0f),"Exit",boost::bind(&MainMenu::callbackExit,this)));
	}
}

void MainMenu::reinit() {
	buttons.clear();
	initialized = false;
	init();
}

unsigned short MainMenu::update(float deltaTime) {

	// event handling
	sf::Event Event;
    while (renderWindow.PollEvent(Event)) {
        if (Event.Type == sf::Event::Closed)
            renderWindow.Close();
		else if (Event.Type == sf::Event::KeyPressed && Event.Key.Code == sf::Keyboard::Escape)
			if(gameStarted)
				return Game::SINGLEPLAYER;
			else
				renderWindow.Close();
		else if (Event.Type == sf::Event::MouseButtonReleased && Event.MouseButton.Button == sf::Mouse::Left) {
			return handleMouseClick(Event.MouseButton.X,Event.MouseButton.Y);
		}
    }

	// mouse over effect
	for(unsigned int i = 0; i < buttons.size(); ++i) {
		if((sf::Mouse::GetPosition(renderWindow).x > buttons[i].getPosition().x && sf::Mouse::GetPosition(renderWindow).x < (buttons[i].getPosition().x+buttons[i].getSize().x)) && (sf::Mouse::GetPosition(renderWindow).y > buttons[i].getPosition().y && sf::Mouse::GetPosition(renderWindow).y < (buttons[i].getPosition().y+buttons[i].getSize().y))) {
			buttons[i].setActive(true);
		} else {
			buttons[i].setActive(false);
		}
	}

	return Game::MAIN_MENU;
}

void MainMenu::draw() {

	renderWindow.Draw(background);

	// draw buttons
	unsigned int size = buttons.size();
	for(unsigned int i = 0; i < size; ++i) {
		buttons[i].draw(renderWindow);
	}
}

unsigned short MainMenu::handleMouseClick(int mouseX, int mouseY) {

	for(unsigned int i = 0; i < buttons.size(); ++i) {
		float posX = buttons[i].getPosition().x;
		float posY = buttons[i].getPosition().y;
		float width = buttons[i].getSize().x;
		float height = buttons[i].getSize().y;

		if((mouseX > posX && mouseX < (posX+width)) && (mouseY > posY && mouseY < (posY+height))) {
			return buttons[i].onClick();
		}
	}

	return Game::MAIN_MENU;
}

int MainMenu::callbackNewGame() {
	if(!gameStarted) {
		gameStarted = true;
	} else {
		// reinit singleplayer gamestate
	}
	return Game::SINGLEPLAYER;
}

int MainMenu::callbackExit() {
	renderWindow.Close();
	return Game::MAIN_MENU;
}