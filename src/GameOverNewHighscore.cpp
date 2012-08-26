/**
* Copyright (c) 2012, Jens Mölzer
* This file is part of the asteroids project and is realeased under the BSD 2-Clause License.
* For more Details on licensing, see 'LICENCE.txt'.
**/

#include "GameOverNewHighscore.hpp"

GameOverNewHighscore::GameOverNewHighscore(sf::RenderWindow& renderWindow) :
    renderWindow(renderWindow),
    initialized(false),
    btnOK(sf::Vector2f((Game::getHandle().getResolution().x / 2) - 166.0f, Game::getHandle().getResolution().y - 120.f),"OK",boost::bind(&GameOverNewHighscore::callbackOK,this),renderWindow),
    maxNameLength(10)
{
    texBackground = Game::getHandle().textureManager.acquire(thor::Resources::fromFile<sf::Texture>("res/menuBackground.png"));
    font = Game::getHandle().fontManager.acquire(thor::Resources::fromFile<sf::Font>("res/font.ttf"));

    txtTitle.setFont(*font);
    txtTitle.setString("Game Over!");
    txtTitle.setCharacterSize(60);
    txtTitle.setColor(sf::Color(244,215,3));
    txtTitle.setPosition(Game::getHandle().getResolution().x/2 - txtTitle.getGlobalBounds().width/2, 130.0f);

    txtNewHighscore.setFont(*font);
    txtNewHighscore.setString("New Highscore!");
    txtNewHighscore.setCharacterSize(50);
    txtNewHighscore.setColor(sf::Color(244,215,3));
    txtNewHighscore.setPosition(Game::getHandle().getResolution().x/2 - txtNewHighscore.getGlobalBounds().width/2, 250.0f);

    txtName.setFont(*font);
    txtName.setPosition(50.0f, 400.0f);
    txtName.setCharacterSize(30);
    txtName.setColor(sf::Color(244,215,3));

    init();
}

void GameOverNewHighscore::init() {
    if(!initialized) {
        background.setTexture(*texBackground);
        background.setPosition(0.0f,0.0f);
    }
}

void GameOverNewHighscore::reinit() {
    initialized = false;
    init();
}

unsigned short GameOverNewHighscore::update(float deltaTime) {

    newState = Game::GAME_OVER_NEW_HIGHSCORE;

    // event handling
    sf::Event event;
    while(renderWindow.pollEvent(event)) {
        if(event.type == sf::Event::Closed)
            renderWindow.close();
        else if(event.type == sf::Event::TextEntered && static_cast<char>(event.text.unicode) > 31 && static_cast<char>(event.text.unicode) < 127 && name.length() < maxNameLength)
            name += static_cast<char>(event.text.unicode);
        else if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::BackSpace && name.length() > 0)
            name.erase(name.end()-1);
    }

    btnOK.update(deltaTime);
    txtName.setString("Enter name: " + name);

    return newState;
}

void GameOverNewHighscore::draw() {

    renderWindow.draw(background);
    renderWindow.draw(txtTitle);
    renderWindow.draw(txtNewHighscore);
    renderWindow.draw(txtName);

    btnOK.draw();

}

void GameOverNewHighscore::callbackOK() {
    Game::getHandle().highscore.saveCurrentScore(name);
    Game::getHandle().highscore.saveToFile("highscore.csv");
    newState = Game::HIGHSCORE_VIEW;
}