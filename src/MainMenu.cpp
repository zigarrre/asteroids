#include "MainMenu.hpp"

using namespace std;

MainMenu::MainMenu(sf::RenderWindow& renderWindow) :
	renderWindow(renderWindow),
	gameStarted(false)
{
	buttons.push_back(Button(sf::Vector2f(50.0f,50.0f),"New Game",&callbackNewGame));
}

unsigned short MainMenu::update(float deltaTime) {
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
	return Game::MAIN_MENU;
}

void MainMenu::draw() {
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
			} else {
				return Game::MAIN_MENU;
			}
		}
	}

	return Game::MAIN_MENU;
}

int callbackNewGame() {
	return Game::SINGLEPLAYER;
}