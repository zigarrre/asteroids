/**
* Copyright (c) 2012, Jens Mölzer
* This file is part of the asteroids project and is realeased under the BSD 2-Clause License.
* For more Details on licensing, see 'LICENCE.txt'.
**/

#pragma once

#include "HUD.hpp"
#include "Gamestate.hpp"
#include "Entity.hpp"
#include "Spaceship.hpp"
#include "Asteroid.hpp"
#include "EntityManager.hpp"
#include "MessageReceiver.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <Thor/Resources.hpp>
#include <Thor/Math.hpp>

class Singleplayer : public Gamestate, public MessageReceiver
{
    public:
        Singleplayer(sf::RenderWindow& renderWindow);
        //~Singleplayer();
        virtual void init();
        virtual void reinit();
        virtual unsigned short update(float deltaTime);
        virtual void draw();
        int getLevel() const { return level; }
        unsigned int getLifes() const { return lifes; }
        unsigned int getScore() const { return score; }
        virtual void receiveMessage(unsigned int msg, const std::vector<boost::any>& params);

        enum { SPACESHIP };

        static EntityManager entityManager;

    protected:
    private:
        sf::RenderWindow& renderWindow;
        bool initialized;
        HUD hud;
        thor::ResourcePtr<sf::Texture> texBackground;
        sf::Sprite background;
        sf::FloatRect saveZone;
        int level;
        unsigned int lifes;
        unsigned int score;

        void spawnAsteroids(int lvl);
};
