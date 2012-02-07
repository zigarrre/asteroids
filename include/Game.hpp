#pragma once

#include "Gamestate.hpp"
#include "Singleplayer.hpp"
#include "MainMenu.hpp"
#include "GamestateManager.hpp"
#include <SFML/Graphics.hpp>
#include <Thor/Resources.hpp>
#include <map>
#include <algorithm>

class Game {

    public:
        Game();
        //~Game();
        void startGameLoop();
		static sf::Vector2i getResolution();

		static thor::ResourceManager<sf::Texture> textureManager;
		static thor::ResourceManager<sf::Font> fontManager;
		
		static GamestateManager gamestateManager;

		enum {
			SINGLEPLAYER,
			MAIN_MENU
		};

    protected:
    private:
        sf::RenderWindow renderWindow;
        float updateTime;

		static sf::Vector2i resolution;
};
