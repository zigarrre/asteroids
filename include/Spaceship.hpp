#ifndef SPACESHIP_HPP
#define SPACESHIP_HPP

#include "Entity.hpp"
#include "Game.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>

class Spaceship : public Entity
{
    public:
        Spaceship(const sf::Texture& tex, const sf::Vector2f& pos);
        virtual void update(float deltaTime);
    protected:
    private:
        float accelerationToSet;
		float rotationspeed;
		const static float PI;
};

#endif // SPACESHIP_HPP
