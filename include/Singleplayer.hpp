#ifndef SINGLEPLAYERGAME_HPP
#define SINGLEPLAYERGAME_HPP

#include "include/Gamestate.hpp"
#include "include/Entity.hpp"
#include "include/Spaceship.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

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
        sf::Image spaceship;
        std::vector<Entity*> entitys;
};

#endif // SINGLEPLAYERGAME_HPP
