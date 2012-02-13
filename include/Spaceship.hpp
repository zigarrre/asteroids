#pragma once

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
		virtual void collide(unsigned int id);
		void takeDamage(float damage);
		virtual void rcvMessage(unsigned int msg);
		unsigned int getLifes() const { return lifes; }
		virtual void reset();

    protected:
    private:
        float accelerationToSet;
		float rotationspeed;
		float weaponCooldown;
		float weaponCooldownToSet;
		float friction;
		unsigned int lifes;
		float hp; // health points
		float spawnMode; // remaining time in spawnMode
		thor::ResourcePtr<sf::Texture> texture;
};
