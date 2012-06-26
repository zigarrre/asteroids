/**
* Copyright (c) 2012, Jens Mölzer
* This file is part of the asteroids project and is realeased under the BSD 2-Clause License.
* For more Details on licensing, see 'LICENCE.txt'.
**/

#include "GameOver.hpp"

GameOver::GameOver(sf::RenderWindow& renderWindow) :
    renderWindow(renderWindow),
    initialized(false),
    btnRestart(sf::Vector2f((Game::getHandle().getResolution().x / 2) - 343.0f, Game::getHandle().getResolution().y - 120.f),"Restart",boost::bind(&GameOver::callbackRestart,this),renderWindow),
    btnMenu(sf::Vector2f((Game::getHandle().getResolution().x / 2) + 10.0f, Game::getHandle().getResolution().y - 120.f),"Menu",boost::bind(&GameOver::callbackMenu,this),renderWindow)
{
    texBackground = Game::getHandle().textureManager.acquire(thor::Resources::TextureKey::fromFile("res/menuBackground.png"));
    font = Game::getHandle().fontManager.acquire(thor::Resources::FontKey::fromFile("res/font.ttf"));

    txtTitle.setFont(*font);
    txtTitle.setString("Game Over!");
    txtTitle.setCharacterSize(60);
    txtTitle.setColor(sf::Color(244,215,3));
    txtTitle.setPosition(Game::getHandle().getResolution().x/2 - txtTitle.getGlobalBounds().width/2, 130.0f);

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
    }

    btnRestart.update(deltaTime);
    btnMenu.update(deltaTime);

    return newState;
}

void GameOver::draw() {

    renderWindow.draw(background);
    renderWindow.draw(txtTitle);

    btnRestart.draw();
    btnMenu.draw();

}

void GameOver::callbackMenu() {
    Game::getHandle().gamestateManager.get(Game::MAIN_MENU)->reinit();
    newState = Game::MAIN_MENU;
}

void GameOver::callbackRestart() {
    Game::getHandle().gamestateManager.get(Game::SINGLEPLAYER)->reinit();
    newState = Game::SINGLEPLAYER;
}