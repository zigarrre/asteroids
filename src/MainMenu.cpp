/**
* Copyright (c) 2012, Jens Mölzer
* This file is part of the asteroids project and is realeased under the BSD 2-Clause License.
* For more Details on licensing, see 'LICENCE.txt'.
**/

#include "MainMenu.hpp"
#include "MessageSystem.hpp"
#include "Messages.hpp"

MainMenu::MainMenu(sf::RenderWindow& renderWindow) :
    initialized(false),
    gameStarted(false),
    renderWindow(renderWindow),
    btnResume(sf::Vector2f(340.0f,270.0f),"Resume",boost::bind(&MainMenu::callbackResume,this),renderWindow),
    btnNewGame(sf::Vector2f(340.0f,350.0f),"New Game",boost::bind(&MainMenu::callbackNewGame,this),renderWindow),
    btnHighscore(sf::Vector2f(340.0f,430.0f),"Highscore",boost::bind(&MainMenu::callbackHighscore,this),renderWindow),
    btnExit(sf::Vector2f(340.0f,510.0f),"Exit",boost::bind(&MainMenu::callbackExit,this),renderWindow)
{
    texBackground = Game::getHandle().textureManager.acquire(thor::Resources::fromFile<sf::Texture>("res/menuBackground.png"));
    font = Game::getHandle().fontManager.acquire(thor::Resources::fromFile<sf::Font>("res/font.ttf"));

    txtTitle.setFont(*font);
    txtTitle.setString("Asteroids");
    txtTitle.setCharacterSize(60);
    txtTitle.setColor(sf::Color(244,215,3));
    txtTitle.setPosition(Game::getHandle().getResolution().x/2 - txtTitle.getGlobalBounds().width/2, 130.0f);

    MessageSystem::getHandle().registerReceiver(this);

    init();
}

MainMenu::~MainMenu() {
    MessageSystem::getHandle().unregisterReceiver(this);
}

void MainMenu::init() {
    if(!initialized) {

        gameStarted = false;

        background.setTexture(*texBackground);
        background.setPosition(0.0f,0.0f);

        version.setString("vO.1.7 alpha"); // 'O' because it looks much better than a real '0' in the used game font
        version.setFont(*font);
        version.setCharacterSize(10);
        version.setColor(sf::Color::White);
        version.setPosition(Game::getHandle().getResolution().x - version.getLocalBounds().width - 20, Game::getHandle().getResolution().y - version.getLocalBounds().height - 20);

        btnResume.setEnabled(false);

    }
}

void MainMenu::reinit() {
    initialized = false;
    init();
}

unsigned short MainMenu::update(float deltaTime) {

    newState = Game::MAIN_MENU;

    // event handling
    sf::Event Event;
    while (renderWindow.pollEvent(Event)) {
        if (Event.type == sf::Event::Closed)
            renderWindow.close();
        else if (Event.type == sf::Event::KeyPressed && Event.key.code == sf::Keyboard::Escape)
            if(gameStarted)
                newState = Game::SINGLEPLAYER;
            else
                renderWindow.close();
    }

    btnResume.update(deltaTime);
    btnNewGame.update(deltaTime);
    btnHighscore.update(deltaTime);
    btnExit.update(deltaTime);

    return newState;
}

void MainMenu::draw() {

    renderWindow.draw(background);
    renderWindow.draw(txtTitle);
    renderWindow.draw(version);

    btnResume.draw();
    btnNewGame.draw();
    btnHighscore.draw();
    btnExit.draw();
}

void MainMenu::receiveMessage(unsigned int msg, const std::vector<boost::any>& params) {
    switch(msg) {
    
    case EngineMessages::GAME_STARTED:
        gameStarted = true;
        btnResume.setEnabled(true);
        break;
    
    case EngineMessages::GAME_OVER:
        gameStarted = false;
        btnResume.setEnabled(false);
        break;

    }
}

void MainMenu::callbackNewGame() {
    if(!gameStarted) {
        gameStarted = true;
        btnResume.setEnabled(true);
    }
    Game::getHandle().gamestateManager.get(Game::SINGLEPLAYER)->reinit();
    newState = Game::SINGLEPLAYER;
}

void MainMenu::callbackExit() {
    renderWindow.close();
}

void MainMenu::callbackResume() {
    if(gameStarted)
        newState = Game::SINGLEPLAYER;
}

void MainMenu::callbackHighscore() {
    newState = Game::HIGHSCORE_VIEW;
}
