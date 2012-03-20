/**
* Copyright (c) 2012, Jens Mölzer
* This file is part of the asteroids project and is realeased under the BSD 2-Clause License.
* For more Details on licensing, see 'LICENCE.txt'.
**/

#include "MainMenu.hpp"

MainMenu::MainMenu(sf::RenderWindow& renderWindow) :
	renderWindow(renderWindow),
	gameStarted(false),
	initialized(false),
	btnResume(sf::Vector2f(340.0f,300.0f),"Resume",boost::bind(&MainMenu::callbackResume,this),renderWindow),
	btnNewGame(sf::Vector2f(340.0f,400.0f),"New Game",boost::bind(&MainMenu::callbackNewGame,this),renderWindow),
	btnExit(sf::Vector2f(340.0f,500.0f),"Exit",boost::bind(&MainMenu::callbackExit,this),renderWindow)

{
	texBackground = Game::textureManager.acquire(thor::Resources::TextureKey::fromFile("res/menuBackground.png"));
	font = Game::fontManager.acquire(thor::Resources::FontKey::fromFile("res/font.ttf"));
	init();
}

void MainMenu::init() {
	if(!initialized) {

		gameStarted = false;

		background.setTexture(*texBackground);
		background.setPosition(0.0f,0.0f);

		version.setString("vO.1 alpha"); // 'O' because it looks much better than real '0' in the used game font
		version.setFont(*font);
		version.setCharacterSize(10);
		version.setColor(sf::Color::White);
		version.setPosition(Game::getResolution().x - version.getLocalBounds().width - 20, Game::getResolution().y - version.getLocalBounds().height - 20);

		btnResume.setEnabled(false);

	}
}

void MainMenu::reinit() {
	initialized = false;
	init();
}

unsigned short MainMenu::update(float deltaTime) {

	// event handling
	sf::Event Event;
    while (renderWindow.pollEvent(Event)) {
        if (Event.type == sf::Event::Closed)
            renderWindow.close();
		else if (Event.type == sf::Event::KeyPressed && Event.key.code == sf::Keyboard::Escape)
			if(gameStarted)
				return Game::SINGLEPLAYER;
			else
				renderWindow.close();
		else if (Event.type == sf::Event::MouseButtonReleased && Event.mouseButton.button == sf::Mouse::Left) {
			return handleMouseClick(sf::Vector2i(Event.mouseButton.y,Event.mouseButton.y));
		}
    }

	btnResume.update(deltaTime);
	btnNewGame.update(deltaTime);
	btnExit.update(deltaTime);

	return Game::MAIN_MENU;
}

void MainMenu::draw() {

	renderWindow.draw(background);
	renderWindow.draw(version);

	btnResume.draw();
	btnNewGame.draw();
	btnExit.draw();
}

unsigned short MainMenu::handleMouseClick(const sf::Vector2i& mouseCord) {

	if(btnResume.isOver(mouseCord))
		return btnResume.onClick();
	else if(btnNewGame.isOver(mouseCord))
		return btnNewGame.onClick();
	else if(btnExit.isOver(mouseCord))
		return btnExit.onClick();
	else
		return Game::MAIN_MENU;
}

int MainMenu::callbackNewGame() {
	if(!gameStarted) {
		gameStarted = true;
		btnResume.setEnabled(true);
	}
	Game::gamestateManager.get(Game::SINGLEPLAYER)->reinit();
	return Game::SINGLEPLAYER;
}

int MainMenu::callbackExit() {
	renderWindow.close();
	return Game::MAIN_MENU;
}

int MainMenu::callbackResume() {
	if(gameStarted) {
		return Game::SINGLEPLAYER;
	} else {
		return Game::MAIN_MENU;
	}
}