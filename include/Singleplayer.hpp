#pragma once

#include "HUD.hpp"
#include "Gamestate.hpp"
#include "Entity.hpp"
#include "Spaceship.hpp"
#include "Asteroid.hpp"
#include "EntityManager.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <iostream>

class Singleplayer : public Gamestate
{
    public:
        Singleplayer(sf::RenderWindow& renderWindow);
        //~Singleplayer();
		virtual void init();
		virtual void reinit();
        virtual unsigned short update(float deltaTime);
        virtual void draw();

		enum { SPACESHIP };

		static EntityManager entityManager;

    protected:
    private:
        sf::RenderWindow& renderWindow;
		bool initialized;
		HUD hud;
};
