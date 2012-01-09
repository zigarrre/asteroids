#ifndef SPACESHIP_HPP
#define SPACESHIP_HPP

#include "Entity.hpp"
#include "Game.hpp"
#include "EnergyBullet.hpp"
#include "utility.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <Thor/Resources.hpp>
#include <vector>
#include <algorithm>

class Spaceship : public Entity
{
    public:
        Spaceship(const sf::Vector2f& pos);
        virtual void update(float deltaTime);
    protected:
    private:
        float accelerationToSet;
		float rotationspeed;
		float weaponCooldown;
		float weaponCooldownToSet;
		float friction;
		thor::ResourcePtr<sf::Texture> texture;
};

#endif // SPACESHIP_HPP
