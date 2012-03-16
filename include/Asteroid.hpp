/**
* Copyright (c) 2012, Jens Mölzer
* This file is part of the asteroids project and is realeased under the BSD 2-Clause License.
* For more Details on licensing, see 'LICENCE.txt'.
**/

#pragma once

#include "Entity.hpp"
#include "Game.hpp"
#include "utility.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <Thor/Resources.hpp>
#include <cmath>

class Asteroid : public Entity {
public:
	static enum Size {SMALL,MEDIUM,BIG};

	Asteroid() {}
	Asteroid(const sf::Vector2f& pos, const sf::Vector2f& velocity, unsigned short size, float rotation = 0.0f, float rotationVelocity = 0.0f);
	~Asteroid() { --asteroidCount; }
	void update(float deltaTime);
	void collide(unsigned int id);
	void rcvMessage(unsigned int msg);
	void takeDamage(float damage);
	static int getAsteroidCount() { return asteroidCount; }
	void reset() {}
private:
	bool running;
	float rotationVelocity;
	float hp; // Health Points
	short size;
	float spread;
	thor::ResourcePtr<sf::Texture> texture;

	static int asteroidCount;
};