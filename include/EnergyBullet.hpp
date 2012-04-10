/**
* Copyright (c) 2012, Jens Mölzer
* This file is part of the asteroids project and is realeased under the BSD 2-Clause License.
* For more Details on licensing, see 'LICENCE.txt'.
**/

#pragma once

#include "Entity.hpp"
#include "Game.hpp"
#include "utility.hpp"
#include "Asteroid.hpp"
#include "EntityTypes.hpp"
#include <Thor/Resources.hpp>
#include <SFML/Graphics.hpp>

class EnergyBullet : public Entity {

public:
    EnergyBullet(EntityManager& manager) : Entity(manager) {}
	EnergyBullet(EntityManager& manager, const sf::Vector2f& pos, float velocity, float angle);
	virtual void update(float deltaTime);
	void setRunning(bool run) { running = run; }
	bool getRunning() { return running; }
	virtual void collide(unsigned int id);
	virtual void rcvMessage(unsigned int msg);
	virtual void reset() {}
    unsigned int getType() const { return EntityTypes::ENERGY_BULLET; }

private:
	bool running;
	float timeToLive;
	bool destroyed;
	float damage;
	thor::ResourcePtr<sf::Texture> texture;
};