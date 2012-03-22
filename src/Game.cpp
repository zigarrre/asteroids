/**
* Copyright (c) 2012, Jens Mölzer
* This file is part of the asteroids project and is realeased under the BSD 2-Clause License.
* For more Details on licensing, see 'LICENCE.txt'.
**/

#include "Game.hpp"

using namespace std;
namespace po = boost::program_options;

sf::Vector2i Game::resolution(1000, 750);
thor::ResourceManager<sf::Texture> Game::textureManager;
thor::ResourceManager<sf::Font> Game::fontManager;
GamestateManager Game::gamestateManager;
po::variables_map Game::config;

Game::Game() :
	renderWindow(sf::VideoMode(resolution.x, resolution.y, 32), "Asteoriden"),
    updateTime(1.0f/120.0f)
{

	po::options_description confDesc("Config");
	confDesc.add_options()
		("spaceship.acceleration", po::value<float>()->default_value(300.0f))
		("spaceship.rotationSpeed", po::value<float>()->default_value(300.0f))
		("spaceship.weaponCooldown", po::value<float>()->default_value(0.17f))
		("spaceship.friction", po::value<float>()->default_value(100.0f))
		("spaceship.lifes", po::value<unsigned int>()->default_value(3))
		("spaceship.hp", po::value<float>()->default_value(1.0f))

		("energyBullet.speed", po::value<float>()->default_value(400.0f))
		("energyBullet.timeToLive", po::value<float>()->default_value(0.85f))
		("energyBullet.damage", po::value<float>()->default_value(1.0f))

		("asteroid.hp", po::value<float>()->default_value(1.0f))
		("asteroid.spread", po::value<float>()->default_value(25.0f))
		("asteroid.minSpeed", po::value<float>()->default_value(50.0f))
		("asteroid.maxSpeed", po::value<float>()->default_value(150.0f))
	;
	
	ifstream file;
    file.open("config.cfg");
	po::store(po::parse_config_file(file,confDesc), config);
    file.close();
	file.close();
    po::notify(config);

	renderWindow.setVerticalSyncEnabled(true);
	renderWindow.setFramerateLimit(60);

	gamestateManager.add(new Singleplayer(renderWindow), SINGLEPLAYER);
	gamestateManager.add(new MainMenu(renderWindow), MAIN_MENU);
	gamestateManager.add(new GameOver(renderWindow), GAME_OVER);
	gamestateManager.setActiveState(MAIN_MENU);
}

void Game::startGameLoop() {

    float frameTime;
    float delta;
    sf::Clock frameClock;

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

sf::Vector2i Game::getResolution() {
	return resolution;
}
