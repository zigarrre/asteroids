#pragma once

#include "Entity.hpp"
#include "Game.hpp"
#include "utility.hpp"
#include <Thor/Resources.hpp>
#include <SFML/Graphics.hpp>

class EnergyBullet : public Entity {

public:
	EnergyBullet(const sf::Vector2f& pos, float angle);
	virtual void update(float deltaTime);
	void setRunning(bool run) { running = run; }
	bool getRunning() { return running; }
	virtual void collide(unsigned int id);
	virtual void rcvMessage(unsigned int msg);

private:
	bool running;
	float speed;
	float timeToLive;
	thor::ResourcePtr<sf::Texture> texture;
};