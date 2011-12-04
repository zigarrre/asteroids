#ifndef GAME_HPP
#define GAME_HPP

#include "include/Gamestate.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>

class Game {
    public:
        Game(sf::RenderWindow& renderWindow, float updateTime);
        void startGameLoop();
    protected:
    private:
        sf::RenderWindow& renderWindow;
        float updateTime;
        std::vector<Gamestate> gamestates;
        int activeState;
};

#endif // GAME_HPP
