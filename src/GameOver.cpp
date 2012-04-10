/**
* Copyright (c) 2012, Jens Mölzer
* This file is part of the asteroids project and is realeased under the BSD 2-Clause License.
* For more Details on licensing, see 'LICENCE.txt'.
**/

#include "GameOver.hpp"

GameOver::GameOver(sf::RenderWindow& renderWindow) :
	renderWindow(renderWindow),
	initialized(false),
	btnRestart(sf::Vector2f(340.0f,400.0f),"Restart",boost::bind(&GameOver::callbackRestart,this),renderWindow),
	btnMenu(sf::Vector2f(340.0f,500.0f),"Menu",boost::bind(&GameOver::callbackMenu,this),renderWindow)

{
	texBackground = Game::textureManager.acquire(thor::Resources::TextureKey::fromFile("res/gameOverBackground.png"));
	init();
}

void GameOver::init() {
	if(!initialized) {
		background.setTexture(*texBackground);
		background.setPosition(0.0f,0.0f);
	}
}

void GameOver::reinit() {
	initialized = false;
	init();
}

unsigned short GameOver::update(float deltaTime) {

	// event handling
	sf::Event Event;
    while (renderWindow.pollEvent(Event)) {
        if (Event.type == sf::Event::Closed)
            renderWindow.close();
		else if (Event.type == sf::Event::MouseButtonReleased && Event.mouseButton.button == sf::Mouse::Left) {
			return handleMouseClick(sf::Vector2i(Event.mouseButton.x,Event.mouseButton.y));
		}
    }

	btnRestart.update(deltaTime);
	btnMenu.update(deltaTime);

	return Game::GAME_OVER;
}

void GameOver::draw() {

	renderWindow.draw(background);

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
	Game::gamestateManager.get(Game::MAIN_MENU)->reinit();
	return Game::MAIN_MENU;
}

int GameOver::callbackRestart() {
	Game::gamestateManager.get(Game::SINGLEPLAYER)->reinit();
	return Game::SINGLEPLAYER;
}