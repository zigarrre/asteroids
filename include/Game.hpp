/**
* Copyright (c) 2012, Jens Mölzer
* This file is part of the asteroids project and is realeased under the BSD 2-Clause License.
* For more Details on licensing, see 'LICENCE.txt'.
**/

#pragma once

#include "Gamestate.hpp"
#include "GamestateManager.hpp"
#include "Highscore.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Thor/Resources.hpp>
#include <map>
#include <algorithm>
#include <boost/program_options.hpp>
#include <fstream>

/**
* The main class of the game
* Call startGameLoop() to start the game
*
* This class is a singleton (constructor private) and the handler can be obtained with getHandle()
**/
class Game {

    public:

        /**
        * Obtain a reference to the singleton
        **/
        static Game& getHandle();

        /**
        * Initialise Game
        * Must be called before startGameLoop()
        **/
        void init();

        /**
        * starts the game, returns when the game is closed
        **/
        void startGameLoop();

        sf::Vector2i getResolution();
        thor::ResourceCache<sf::Texture> textureManager;
        thor::ResourceCache<sf::Font> fontManager;
        thor::ResourceCache<sf::SoundBuffer> soundManager;
        GamestateManager gamestateManager;
        boost::program_options::variables_map config;
        Highscore highscore;

        // gamesate IDs
        enum {
            SINGLEPLAYER = 0,
            MAIN_MENU,
            GAME_OVER,
            GAME_OVER_NEW_HIGHSCORE,
            HIGHSCORE_VIEW
        };

    protected:
    private:
        Game();
        //~Game();

        bool initialized;
        sf::Vector2i resolution;
        sf::RenderWindow renderWindow;
        float updateTime;

};
