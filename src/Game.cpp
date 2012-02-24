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
		("spaceship.acceleration", po::value<float>()->default_value(1.5f))
		("spaceship.rotationSpeed", po::value<float>()->default_value(200.0f))
		("spaceship.weaponCooldown", po::value<float>()->default_value(0.5f))
		("spaceship.friction", po::value<float>()->default_value(0.2f))
		("spaceship.lifes", po::value<unsigned int>()->default_value(3))
		("spaceship.hp", po::value<float>()->default_value(1.0f))

		("energyBullet.speed", po::value<float>()->default_value(200.0f))
		("energyBullet.timeToLive", po::value<float>()->default_value(3.0f))
		("energyBullet.damage", po::value<float>()->default_value(1.0f))

		("asteroid.hp", po::value<float>()->default_value(1.0f))
		("asteroid.spread", po::value<float>()->default_value(25.0f))
	;
	
	ifstream file;
    file.open("config.cfg");
	po::store(po::parse_config_file(file,confDesc), config);
    file.close();
	file.close();
    po::notify(config);

	renderWindow.EnableVerticalSync(true);
	renderWindow.SetFramerateLimit(60);

	gamestateManager.add(new Singleplayer(renderWindow), SINGLEPLAYER);
	gamestateManager.add(new MainMenu(renderWindow), MAIN_MENU);
	gamestateManager.add(new GameOver(renderWindow), GAME_OVER);
	gamestateManager.setActiveState(MAIN_MENU);
}

void Game::startGameLoop() {

    float frameTime;
    float delta;

    while(renderWindow.IsOpened()) {

        frameTime = renderWindow.GetFrameTime()/1000.0f;

        // Update
        while(frameTime > 0.0f) {
            delta = min(frameTime, updateTime);
			gamestateManager.update(delta);
            frameTime -= delta;
        }

		// Draw
        renderWindow.Clear();
		gamestateManager.getActiveState()->draw();
        renderWindow.Display();
    }
}

sf::Vector2i Game::getResolution() {
	return resolution;
}
