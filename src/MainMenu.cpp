#include "MainMenu.hpp"

using namespace std;

MainMenu::MainMenu(sf::RenderWindow& renderWindow) :
	renderWindow(renderWindow),
	gameStarted(false)
{

	texBackground = Game::textureManager.Acquire(thor::Resources::TextureKey::FromFile("res/menuBackground.png"));
	background.SetTexture(*texBackground);
	background.SetPosition(0.0f,0.0f);

	buttons.push_back(Button(sf::Vector2f(340.0f,300.0f),"New Game",&callbackNewGame));
	buttons.push_back(Button(sf::Vector2f(340.0f,400.0f),"Exit",&callbackExit));
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
			int rv = buttons[i].onClick();
			if(rv == Game::SINGLEPLAYER) {
				gameStarted = true;
				return rv;
			} else if(rv == -1) {
				renderWindow.Close();
				return Game::MAIN_MENU;
			}
		}
	}

	return Game::MAIN_MENU;
}

int callbackNewGame() {
	return Game::SINGLEPLAYER;
}

int callbackExit() {
	return -1;
}