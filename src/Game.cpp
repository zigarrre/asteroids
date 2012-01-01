#include "Game.hpp"

using namespace std;

sf::Vector2i Game::resolution(600, 500);
thor::ResourceManager<sf::Texture> Game::resourceManager;

Game::Game() :
	renderWindow(sf::VideoMode(resolution.x, resolution.y, 32), "Asteoriden"),
    updateTime(1.0f/120.0f),
    activeState(0)
{
	renderWindow.EnableVerticalSync(true);
	renderWindow.SetFramerateLimit(60);
    gamestates.push_back(new Singleplayer(renderWindow));
}

Game::~Game() {
    for(unsigned int i = 0; i < gamestates.size(); ++i) {
        delete gamestates[i];
        gamestates.erase(gamestates.begin()+i);
    }
}

void Game::startGameLoop() {

    float frameTime;
    float delta;

    while(renderWindow.IsOpened()) {

        frameTime = renderWindow.GetFrameTime()/1000.0f;

        // Update
        while(frameTime > 0.0f) {
            delta = min(frameTime, updateTime);
            activeState = gamestates[0]->update(delta);
            frameTime -= delta;
        }

		// Draw
        renderWindow.Clear();
        gamestates[0]->draw();
        renderWindow.Display();
    }
}

sf::Vector2i Game::getResolution() {
	return resolution;
}
