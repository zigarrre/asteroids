#pragma once

#include "Entity.hpp"
#include "Game.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <Thor/Resources.hpp>

class Asteroid : public Entity {
public:
	static enum Size {BIG,MEDIUM,SMALL};

	Asteroid() {}
	Asteroid(const sf::Vector2f& pos, const sf::Vector2f& velocity, Size size, float rotation = 0.0f, float rotationVelocity = 0.0f);
	void update(float deltaTime);
	void collide(unsigned int id);
	void rcvMessage(unsigned int msg);
	void takeDamage(float damage);
private:
	bool running;
	float rotationVelocity;
	float hp; // Health Points
	Size size;
	thor::ResourcePtr<sf::Texture> texture;
};