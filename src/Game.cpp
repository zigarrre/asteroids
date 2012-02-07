#include "Game.hpp"

using namespace std;

sf::Vector2i Game::resolution(1000, 750);
thor::ResourceManager<sf::Texture> Game::textureManager;
thor::ResourceManager<sf::Font> Game::fontManager;
GamestateManager Game::gamestateManager;

Game::Game() :
	renderWindow(sf::VideoMode(resolution.x, resolution.y, 32), "Asteoriden"),
    updateTime(1.0f/120.0f)
{
	renderWindow.EnableVerticalSync(true);
	renderWindow.SetFramerateLimit(60);

	gamestateManager.add(new Singleplayer(renderWindow), SINGLEPLAYER);
	gamestateManager.add(new MainMenu(renderWindow), MAIN_MENU);
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
