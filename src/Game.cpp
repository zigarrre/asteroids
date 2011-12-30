#include "include/Game.hpp"

using namespace std;

Game::Game(sf::RenderWindow& renderWindow,float updateTime) :
    renderWindow(renderWindow),
    updateTime(updateTime),
    activeState(0)
{
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

        frameTime = renderWindow.GetFrameTime();

        // Update
        while(frameTime > 0.0f) {
            delta = min(frameTime, updateTime);
            activeState = gamestates[0]->update(delta);
            frameTime -= delta;
        }
        renderWindow.Clear();
        gamestates[0]->draw();
        renderWindow.Display();
    }
}
