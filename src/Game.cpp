/**
* Copyright (c) 2012, Jens Mölzer
* This file is part of the asteroids project and is realeased under the BSD 2-Clause License.
* For more Details on licensing, see 'LICENCE.txt'.
**/

#include "Game.hpp"
#include "Singleplayer.hpp"
#include "MainMenu.hpp"
#include "GameOver.hpp"
#include "GameOverNewHighscore.hpp"
#include "HighscoreView.hpp"
#include "config.h"

using namespace std;
namespace po = boost::program_options;

Game& Game::getHandle() {
    static Game game;
    return game;
}

Game::Game() :
    initialized(false),
    resolution(1000, 750),
    renderWindow(sf::VideoMode(resolution.x, resolution.y, 32), "asteroids"),
    updateTime(1.0f/120.0f)
{
}

void Game::init() {
    if(initialized) // allready initialized
        return;

    po::options_description confDesc("Config");
    confDesc.add_options()
        ("paths.res", po::value<string>()->default_value(ASTEROIDS_PATHS_RES))
        ("paths.highscore", po::value<string>()->default_value(ASTEROIDS_PATHS_HIGHSCORE))
        ("paths.highscoreHome", po::value<bool>()->default_value(ASTEROIDS_PATHS_HIGHSCORE_HOME))

        ("spaceship.acceleration", po::value<float>()->default_value(300.0f))
        ("spaceship.rotationSpeed", po::value<float>()->default_value(300.0f))
        ("spaceship.weaponCooldown", po::value<float>()->default_value(0.17f))
        ("spaceship.friction", po::value<float>()->default_value(100.0f))
        ("spaceship.lifes", po::value<unsigned int>()->default_value(3))
        ("spaceship.hp", po::value<int>()->default_value(1))

        ("energyBullet.speed", po::value<float>()->default_value(400.0f))
        ("energyBullet.timeToLive", po::value<float>()->default_value(0.85f))
        ("energyBullet.damage", po::value<float>()->default_value(1.0f))

        ("asteroid.hp", po::value<int>()->default_value(1))
        ("asteroid.spread", po::value<float>()->default_value(25.0f))
        ("asteroid.minSpeed", po::value<float>()->default_value(50.0f))
        ("asteroid.maxSpeed", po::value<float>()->default_value(150.0f))
    ;
    
    ifstream file;
    file.open(ASTEROIDS_PATHS_CONFIG);
    po::store(po::parse_config_file(file,confDesc), config);
    file.close();
    file.close();
    po::notify(config);

    string highscorePath;
    if (config["paths.highscoreHome"].as<bool>())
        highscorePath = rrr::getHomePath() + "/" + config["paths.highscore"].as<string>();
    else
        highscorePath = config["paths.highscore"].as<string>();
    highscore.loadFromFile(highscorePath);

    renderWindow.setVerticalSyncEnabled(true);
    renderWindow.setFramerateLimit(60);

    gamestateManager.add(new Singleplayer(renderWindow), SINGLEPLAYER);
    gamestateManager.add(new MainMenu(renderWindow), MAIN_MENU);
    gamestateManager.add(new GameOver(renderWindow), GAME_OVER);
    gamestateManager.add(new GameOverNewHighscore(renderWindow, highscorePath), GAME_OVER_NEW_HIGHSCORE);
    gamestateManager.add(new HighscoreView(renderWindow), HIGHSCORE_VIEW);
    gamestateManager.setActiveState(MAIN_MENU);

    soundService.init();
    
    initialized = true;
}

void Game::startGameLoop() {
    if(!initialized)
        return;

    float frameTime;
    float delta;

    frameClock.restart();
    while(renderWindow.isOpen()) {

        frameTime = frameClock.getElapsedTime().asSeconds();
        frameClock.restart();
        

        // Update
        while(frameTime > 0.0f) {
            delta = min(frameTime, updateTime);
            gamestateManager.update(delta);
            frameTime -= delta;
        }

        // Draw
        renderWindow.clear();
        gamestateManager.getActiveState()->draw();
        renderWindow.display();
    }
}

void Game::waitForFocus() {
    sf::Event e;
    while (renderWindow.waitEvent(e)) {
        if (e.type == sf::Event::GainedFocus) {
            break;
        }
    }
    frameClock.restart();
}

sf::Vector2i Game::getResolution() {
    return resolution;
}
