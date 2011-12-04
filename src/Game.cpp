#include "include/Game.hpp"

using namespace std;

Game::Game(sf::RenderWindow& renderWindow,float updateTime) :
    renderWindow(renderWindow),
    updateTime(updateTime),
    activeState(0)
{

}

void Game::startGameLoop() {

    float frameTime;
    float delta;

    while(renderWindow.IsOpened()) {

        frameTime = renderWindow.GetFrameTime();

        // Update
        while(frameTime > 0.0f) {
            delta = min(frameTime, updateTime);
            activeState = gamestates[activeState].update(delta);
            frameTime -= delta;
        }

        gamestates[activeState].draw(renderWindow);

    }
}
