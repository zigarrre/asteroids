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

    btnRestart.draw();
    btnMenu.draw();

}

void GameOver::callbackMenu() {
    Game::gamestateManager.get(Game::MAIN_MENU)->reinit();
    newState = Game::MAIN_MENU;
}

void GameOver::callbackRestart() {
    Game::gamestateManager.get(Game::SINGLEPLAYER)->reinit();
    newState = Game::SINGLEPLAYER;
}