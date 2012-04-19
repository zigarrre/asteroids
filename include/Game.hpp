/**
* Copyright (c) 2012, Jens Mölzer
* This file is part of the asteroids project and is realeased under the BSD 2-Clause License.
* For more Details on licensing, see 'LICENCE.txt'.
**/

#pragma once

#include "Gamestate.hpp"
#include "Singleplayer.hpp"
#include "MainMenu.hpp"
#include "GamestateManager.hpp"
#include "GameOver.hpp"
#include <SFML/Graphics.hpp>
#include <Thor/Resources.hpp>
#include <map>
#include <algorithm>
#include <boost/program_options.hpp>
#include <fstream>

class Game {

    public:
        Game();
        //~Game();
        void startGameLoop();
        static sf::Vector2i getResolution();

        static thor::ResourceManager<sf::Texture> textureManager;
        static thor::ResourceManager<sf::Font> fontManager;
        
        static GamestateManager gamestateManager;

        static boost::program_options::variables_map config;

        enum {
            SINGLEPLAYER,
            MAIN_MENU,
            GAME_OVER
        };

    protected:
    private:
        sf::RenderWindow renderWindow;
        float updateTime;

        static sf::Vector2i resolution;
};
