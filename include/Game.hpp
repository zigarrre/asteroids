#ifndef GAME_HPP
#define GAME_HPP

#include "Gamestate.hpp"
#include "Singleplayer.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>

class Game {
    public:
        Game();
        ~Game();
        void startGameLoop();
		static int resolutionX;
		static int resolutionY;
    protected:
    private:
        sf::RenderWindow renderWindow;
        float updateTime;
        std::vector<Gamestate*> gamestates;
        int activeState;
};

#endif // GAME_HPP
