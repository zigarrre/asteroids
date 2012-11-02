/**
* Copyright (c) 2012, Jens Mölzer
* This file is part of the asteroids project and is realeased under the BSD 2-Clause License.
* For more Details on licensing, see 'LICENCE.txt'.
**/

#include "HighscoreView.hpp"
#include "utility.hpp"
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

HighscoreView::HighscoreView(sf::RenderWindow& renderWindow) :
    initialized(false),
    renderWindow(renderWindow),
    btnRestart(sf::Vector2f((Game::getHandle().getResolution().x / 2) - 343.0f, Game::getHandle().getResolution().y - 120.f),"Restart",boost::bind(&HighscoreView::callbackRestart,this),renderWindow),
    btnMenu(sf::Vector2f((Game::getHandle().getResolution().x / 2) + 10.0f, Game::getHandle().getResolution().y - 120.f),"Menu",boost::bind(&HighscoreView::callbackMenu,this),renderWindow),
    txtTableScore(10) // put 10 elements into vector
{
    texBackground = Game::getHandle().textureManager.acquire(thor::Resources::fromFile<sf::Texture>("res/menuBackground.png"));
    font = Game::getHandle().fontManager.acquire(thor::Resources::fromFile<sf::Font>("res/font.ttf"));

    txtTitle.setFont(*font);
    txtTitle.setString("Highscores");
    txtTitle.setCharacterSize(60);
    txtTitle.setColor(sf::Color(244,215,3));
    txtTitle.setPosition(Game::getHandle().getResolution().x/2 - txtTitle.getGlobalBounds().width/2, 130.0f);

    txtTableNumber.setFont(*font);
    txtTableNumber.setPosition(230.0f, 240.0f);
    txtTableNumber.setCharacterSize(25);
    txtTableNumber.setColor(sf::Color(244,215,3));

    txtTableName.setFont(*font);
    txtTableName.setPosition(330.0f, 240.0f);
    txtTableName.setCharacterSize(25);
    txtTableName.setColor(sf::Color(244,215,3));

    for(unsigned int i = 0; i < txtTableScore.size(); ++i) {
        txtTableScore[i].setFont(*font);
        txtTableScore[i].setCharacterSize(25);
        txtTableScore[i].setColor(sf::Color(244,215,3));
    }

    init();
}

void HighscoreView::init() {
    if(!initialized) {
        background.setTexture(*texBackground);
        background.setPosition(0.0f,0.0f);
    }
}

void HighscoreView::reinit() {
    initialized = false;
    init();
}

unsigned short HighscoreView::update(float deltaTime) {

    newState = Game::HIGHSCORE_VIEW;

    // event handling
    sf::Event event;
    while(renderWindow.pollEvent(event)) {
        if(event.type == sf::Event::Closed)
            renderWindow.close();
    }

    static bool tableUpToDate = false;
    if(!tableUpToDate) { // prevent unneeded updates
        // fill table with content
        string tableNumber = "", tableName = "";
        for(unsigned int i = 0; i < 10; ++i) {
            tableNumber += rrr::toString(i+1) + ".\n";
            tableName += Game::getHandle().highscore[i].name + '\n';
            txtTableScore[i].setString(rrr::toString(Game::getHandle().highscore[i].score));
            txtTableScore[i].setOrigin(txtTableScore[i].getLocalBounds().width, 0); // set origin to upper right corner (for right alignment)
            txtTableScore[i].setPosition(770.0f, 240.0f + (i * txtTableScore[i].getFont().getLineSpacing(txtTableScore[i].getCharacterSize())));
        }
        txtTableNumber.setString(tableNumber);
        txtTableName.setString(tableName);
        tableUpToDate = true;
    }

    btnRestart.update(deltaTime);
    btnMenu.update(deltaTime);

    if(newState != Game::HIGHSCORE_VIEW) // Gamestate changes, highscore-data afterwards maybe changed
        tableUpToDate = false;

    return newState;
}

void HighscoreView::draw() {

    renderWindow.draw(background);
    renderWindow.draw(txtTitle);
    renderWindow.draw(txtTableNumber);
    renderWindow.draw(txtTableName);
    for(unsigned int i = 0; i < txtTableScore.size(); ++i)
        renderWindow.draw(txtTableScore[i]);

    btnRestart.draw();
    btnMenu.draw();

}

void HighscoreView::callbackMenu() {
    Game::getHandle().gamestateManager.get(Game::MAIN_MENU)->reinit();
    newState = Game::MAIN_MENU;
}

void HighscoreView::callbackRestart() {
    Game::getHandle().gamestateManager.get(Game::SINGLEPLAYER)->reinit();
    newState = Game::SINGLEPLAYER;
}
