#ifndef GAME_HPP
#define GAME_HPP

#include "Gamestate.hpp"
#include "Singleplayer.hpp"
#include <SFML/Graphics.hpp>
#include <Thor/Resources.hpp>
#include <vector>
#include <algorithm>

class Game {
    public:
        Game();
        ~Game();
        void startGameLoop();
		static sf::Vector2i getResolution();

		static thor::ResourceManager<sf::Texture> resourceManager;
    protected:
    private:
        sf::RenderWindow renderWindow;
        float updateTime;
        std::vector<Gamestate*> gamestates;
        int activeState;

		static sf::Vector2i resolution;
};

#endif // GAME_HPP
