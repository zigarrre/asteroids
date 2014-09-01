/**
* Copyright (c) 2012, Jens Mölzer
* This file is part of the asteroids project and is realeased under the BSD 2-Clause License.
* For more Details on licensing, see 'LICENCE.txt'.
**/

#include "GameOver.hpp"
#include <boost/bind.hpp>

GameOver::GameOver(sf::RenderWindow& renderWindow) :
    initialized(false),
    renderWindow(renderWindow),
    btnManager(sf::Vector2f((Game::getHandle().getResolution().x / 2) - 343.0f, Game::getHandle().getResolution().y - 120.f), renderWindow)
{
    texBackground = Game::getHandle().textureManager.acquire(thor::Resources::fromFile<sf::Texture>(Game::getHandle().config["paths.res"].as<std::string>() + "/menuBackground.png"));
    font = Game::getHandle().fontManager.acquire(thor::Resources::fromFile<sf::Font>(Game::getHandle().config["paths.res"].as<std::string>() + "/font.ttf"));

    txtTitle.setFont(*font);
    txtTitle.setString("Game Over!");
    txtTitle.setCharacterSize(60);
    txtTitle.setColor(sf::Color(244,215,3));
    txtTitle.setPosition(Game::getHandle().getResolution().x/2 - txtTitle.getGlobalBounds().width/2, 130.0f);
    
    btnManager.setLayout(ButtonManager::HORIZONTALLY);
    btnManager.addButton("Restart", boost::bind(&GameOver::callbackRestart, this));
    btnManager.addButton("Menu", boost::bind(&GameOver::callbackMenu, this));

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

    newState = Game::GAME_OVER;

    // event handling
    sf::Event Event;
    while (renderWindow.pollEvent(Event)) {
        if (Event.type == sf::Event::Closed)
            renderWindow.close();
        else if (Event.type == sf::Event::LostFocus)
            Game::getHandle().waitForFocus();
    }

    btnManager.update(deltaTime);

    return newState;
}

void GameOver::draw() {

    renderWindow.draw(background);
    renderWindow.draw(txtTitle);

    btnManager.draw();

}

void GameOver::callbackMenu() {
    newState = Game::MAIN_MENU;
}

void GameOver::callbackRestart() {
    Game::getHandle().gamestateManager.get(Game::SINGLEPLAYER)->reinit();
    newState = Game::SINGLEPLAYER;
}
