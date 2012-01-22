#pragma once

#include "Entity.hpp"
#include "Game.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <Thor/Resources.hpp>

class Asteroid : public Entity {
public:
	Asteroid(const sf::Vector2f& pos, const sf::Vector2f& velocity, float rotation = 0.0f, float rotationVelocity = 0.0f);
	void update(float deltaTime);
private:
	bool running;
	float rotationVelocity;
	thor::ResourcePtr<sf::Texture> texture;
};