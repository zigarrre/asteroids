/**
* Copyright (c) 2012, Jens Mölzer
* This file is part of the asteroids project and is realeased under the BSD 2-Clause License.
* For more Details on licensing, see 'LICENCE.txt'.
**/

#include "EnergyBullet.hpp"

EnergyBullet::EnergyBullet(EntityManager& manager, const sf::Vector2f& pos, float velocity, float angle) :
	running(true),
	timeToLive(3.0f),
	destroyed(false),
    Entity(manager)
{
	
	timeToLive = Game::config["energyBullet.timeToLive"].as<float>();
	damage = Game::config["energyBullet.damage"].as<float>();

	texture = Game::textureManager.acquire(thor::Resources::TextureKey::fromFile("res/bullet1.png")); //TODO needs exeption Handling
    this->setTexture(*texture);
	this->setOrigin(this->getLocalBounds().width/2.0f,this->getLocalBounds().height/2.0f);
	this->setPosition(pos);
	this->setRotation(angle);
	this->velocity[0] = velocity * sin(angle*(PI/180));
	this->velocity[1] = velocity * -cos(angle*(PI/180));
	
	hitbox = rrr::loadHitbox("res/bullet1.col");
}

void EnergyBullet::update(float deltaTime) {
	if(running) {

		if(destroyed) {
			Singleplayer::entityManager.remove(getID());
			return;
		}

		//Time to Live
		if(timeToLive <= 0) {
			Singleplayer::entityManager.remove(getID());
			return;
		} else {
			timeToLive -= deltaTime;
		}

		//move
		this->move(velocity[0] * deltaTime, velocity[1] * deltaTime);

		// if the bullet has left the field, set it to the opposite side
		sf::Vector2f pos = this->getPosition();
		sf::Vector2f size;
		size.x = this->getGlobalBounds().width;
		size.y = this->getGlobalBounds().height;
		sf::Vector2f origin = this->getOrigin();
		if((pos.x + (size.x/2)) < 0) {
			this->setPosition(Game::getResolution().x + (size.x/2), pos.y);
		} else if(pos.x - (size.x/2) > Game::getResolution().x) {
			this->setPosition(-size.x+(size.x/2),pos.y);
		}
		if((pos.y + (size.y/2)) < 0) {
			this->setPosition(pos.x, Game::getResolution().y + (size.y/2));
		} else if(pos.y - (size.y/2) > Game::getResolution().y) {
			this->setPosition(pos.x, -size.y+(size.y/2));
		}
	}
}

void EnergyBullet::collide(unsigned int id) {
	Asteroid* asteroid = dynamic_cast<Asteroid*>(Singleplayer::entityManager.getEntity(id));
	if(asteroid) {
		//cast ok
		asteroid->takeDamage(damage);
	}
	destroyed = true;
}

void EnergyBullet::rcvMessage(unsigned int msg) {

}