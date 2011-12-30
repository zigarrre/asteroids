#ifndef GAME_HPP
#define GAME_HPP

#include "include/Gamestate.hpp"
#include "include/Singleplayer.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>

class Game {
    public:
        Game(sf::RenderWindow& renderWindow, float updateTime);
        ~Game();
        void startGameLoop();
    protected:
    private:
        sf::RenderWindow& renderWindow;
        float updateTime;
        std::vector<Gamestate*> gamestates;
        int activeState;
};

#endif // GAME_HPP
