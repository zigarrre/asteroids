#include "Game.hpp"

using namespace std;

sf::Vector2i Game::resolution(600, 500);
thor::ResourceManager<sf::Texture> Game::textureManager;
thor::ResourceManager<sf::Font> Game::fontManager;

Game::Game() :
	renderWindow(sf::VideoMode(resolution.x, resolution.y, 32), "Asteoriden"),
    updateTime(1.0f/120.0f),
    activeState(MAIN_MENU)
{
	renderWindow.EnableVerticalSync(true);
	renderWindow.SetFramerateLimit(60);
	gamestates.insert(pair<unsigned short,Gamestate*>(SINGLEPLAYER, new Singleplayer(renderWindow)));
	gamestates.insert(pair<unsigned short,Gamestate*>(MAIN_MENU, new MainMenu(renderWindow)));
}

Game::~Game() {
	map<unsigned short, Gamestate*>::iterator it = gamestates.begin();
    for(; it != gamestates.end();) {
		delete it->second;
		it = gamestates.erase(it);
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
            activeState = gamestates[activeState]->update(delta);
            frameTime -= delta;
        }

		// Draw
        renderWindow.Clear();
		gamestates[activeState]->draw();
        renderWindow.Display();
    }
}

sf::Vector2i Game::getResolution() {
	return resolution;
}
