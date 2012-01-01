#ifndef SPACESHIP_HPP
#define SPACESHIP_HPP

#include "Entity.hpp"
#include "Game.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <Thor/Resources.hpp>
#include <vector>

class Spaceship : public Entity
{
    public:
        Spaceship(const sf::Vector2f& pos);
        virtual void update(float deltaTime);
    protected:
    private:
        float accelerationToSet;
		float rotationspeed;
		const static float PI;
		thor::ResourcePtr<sf::Texture> texture;
};

#endif // SPACESHIP_HPP
