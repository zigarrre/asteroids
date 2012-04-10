/**
* Copyright (c) 2012, Jens Mölzer
* This file is part of the asteroids project and is realeased under the BSD 2-Clause License.
* For more Details on licensing, see 'LICENCE.txt'.
**/

#pragma once

#include "Entity.hpp"
#include "Game.hpp"
#include "utility.hpp"
#include "EntityTypes.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <Thor/Resources.hpp>
#include <cmath>
#include <boost/any.hpp>

class Asteroid : public Entity {
public:
	enum Size {SMALL,MEDIUM,BIG};

    Asteroid(EntityManager& manager) : Entity(manager) {}
	Asteroid(EntityManager& manager, const sf::Vector2f& pos, const sf::Vector2f& velocity, unsigned short size, float rotation = 0.0f, float rotationVelocity = 0.0f);
	~Asteroid() { --asteroidCount; }
	void update(float deltaTime);
	void collide(unsigned int id, unsigned int type);
	void rcvMessage(unsigned int msg, const std::vector<boost::any>& params = std::vector<boost::any>());
	static int getAsteroidCount() { return asteroidCount; }
	void reset() {}
    unsigned int getType() const { return EntityTypes::ASTEROID; }
private:
	bool running;
	float rotationVelocity;
	int hp; // Health Points
	short size;
	float spread;
	thor::ResourcePtr<sf::Texture> texture;

	static int asteroidCount;
};