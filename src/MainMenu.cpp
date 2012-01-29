#include "MainMenu.hpp"

using namespace std;

MainMenu::MainMenu(sf::RenderWindow& renderWindow) :
	renderWindow(renderWindow)
{
	// load textures
	thor::Resources::TextureKey key = thor::Resources::TextureKey::FromFile("res/buttons/newGame.png");
	textures.insert(pair<string,thor::ResourcePtr<sf::Texture>>("newGame",Game::resourceManager.Acquire(key)));
	key = thor::Resources::TextureKey::FromFile("res/buttons/exit.png");
	textures.insert(pair<string,thor::ResourcePtr<sf::Texture>>("exit",Game::resourceManager.Acquire(key)));
	//create buttons
	buttons.push_back(sf::Sprite(*textures["newGame"]));
	buttons.push_back(sf::Sprite(*textures["exit"]));
}

Gamestates MainMenu::update(float deltaTime) {
	sf::Event Event;
    while (renderWindow.PollEvent(Event)) {
        if (Event.Type == sf::Event::Closed)
            renderWindow.Close();
    }
	return MAIN_MENU;
}

void MainMenu::draw() {
	// draw buttons
	unsigned int size = buttons.size();
	for(unsigned int i = 0; i < size; ++i) {
		renderWindow.Draw(buttons[i]);
	}
}