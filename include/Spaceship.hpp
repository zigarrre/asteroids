/**
* Copyright (c) 2012, Jens M�lzer
* This file is part of the asteroids project and is realeased under the BSD 2-Clause License.
* For more Details on licensing, see 'LICENCE.txt'.
**/

#pragma once

#include "Entity.hpp"
#include "Game.hpp"
#include "EnergyBullet.hpp"
#include "utility.hpp"
#include "EntityTypes.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <Thor/Resources.hpp>
#include <vector>
#include <algorithm>

class Spaceship : public Entity
{
    public:
        Spaceship(EntityManager& manager) : Entity(manager) {}
        Spaceship(EntityManager& manager, const sf::Vector2f& pos);
        virtual void update(float deltaTime);
		virtual void collide(unsigned int id);
		void takeDamage(float damage);
		virtual void rcvMessage(unsigned int msg, const std::vector<boost::any>& params = std::vector<boost::any>());
		unsigned int getLifes() const { return lifes; }
		virtual void reset();
        unsigned int getType() const { return EntityTypes::SPACESHIP; }

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
		float bulletSpeed;
		thor::ResourcePtr<sf::Texture> texture;
};
