#ifndef SINGLEPLAYERGAME_HPP
#define SINGLEPLAYERGAME_HPP

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
        virtual int update(float deltaTime);
        virtual void draw();

		static EntityManager entityManager;
    protected:
    private:
        sf::RenderWindow& renderWindow;
};

#endif // SINGLEPLAYERGAME_HPP
