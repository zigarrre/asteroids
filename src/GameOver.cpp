#include "GameOver.hpp"

GameOver::GameOver(sf::RenderWindow& renderWindow) :
	renderWindow(renderWindow),
	initialized(false),
	btnRestart(sf::Vector2f(340.0f,400.0f),"Restart",boost::bind(&GameOver::callbackRestart,this),renderWindow),
	btnMenu(sf::Vector2f(340.0f,500.0f),"Menu",boost::bind(&GameOver::callbackMenu,this),renderWindow)

{
	texBackground = Game::textureManager.Acquire(thor::Resources::TextureKey::FromFile("res/gameOverBackground.png"));
	init();
}

void GameOver::init() {
	if(!initialized) {
		background.SetTexture(*texBackground);
		background.SetPosition(0.0f,0.0f);
	}
}

void GameOver::reinit() {
	initialized = false;
	init();
}

unsigned short GameOver::update(float deltaTime) {

	// event handling
	sf::Event Event;
    while (renderWindow.PollEvent(Event)) {
        if (Event.Type == sf::Event::Closed)
            renderWindow.Close();
		else if (Event.Type == sf::Event::MouseButtonReleased && Event.MouseButton.Button == sf::Mouse::Left) {
			return handleMouseClick(sf::Vector2i(Event.MouseButton.X,Event.MouseButton.Y));
		}
    }

	btnRestart.update(deltaTime);
	btnMenu.update(deltaTime);

	return Game::GAME_OVER;
}

void GameOver::draw() {

	renderWindow.Draw(background);

	btnRestart.draw();
	btnMenu.draw();

}

unsigned short GameOver::handleMouseClick(const sf::Vector2i& mouseCord) {

	if(btnRestart.isOver(mouseCord))
		return btnRestart.onClick();
	else if(btnMenu.isOver(mouseCord))
		return btnMenu.onClick();
	else
		return Game::MAIN_MENU;
}

int GameOver::callbackMenu() {
	return Game::MAIN_MENU;
}

int GameOver::callbackRestart() {
	Game::gamestateManager.get(Game::SINGLEPLAYER)->reinit();
	return Game::SINGLEPLAYER;
}