#ifndef SINGLEPLAYERGAME_HPP
#define SINGLEPLAYERGAME_HPP

#include "Gamestate.hpp"
#include "Entity.hpp"
#include "Spaceship.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <iostream>

class Singleplayer : public Gamestate
{
    public:
        Singleplayer(sf::RenderWindow& renderWindow);
        ~Singleplayer();
        virtual int update(float deltaTime);
        virtual void draw();
    protected:
    private:
        sf::RenderWindow& renderWindow;
        sf::Texture texSpaceship;
        std::vector<Entity*> entitys;
};

#endif // SINGLEPLAYERGAME_HPP
