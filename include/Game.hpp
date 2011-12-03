#ifndef GAME_HPP
#define GAME_HPP

#include "include/Gamestate.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

class Game {
    public:
        Game(sf::RenderTarget& renderTarget);
        startGameLoop();
    protected:
    private:
        sf::RenderTarget& renderTarget;
        vector<Gamestate> gamestates;
        int activeState;
};

#endif // GAME_HPP
