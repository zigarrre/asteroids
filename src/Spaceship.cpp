/**
* Copyright (c) 2012, Jens Mölzer
* This file is part of the asteroids project and is realeased under the BSD 2-Clause License.
* For more Details on licensing, see 'LICENCE.txt'.
**/

#include "Spaceship.hpp"

Spaceship::Spaceship(const sf::Vector2f& pos) :
	weaponCooldown(0.0f),
	spawnMode(0.0f)
{
	accelerationToSet = Game::config["spaceship.acceleration"].as<float>();
	rotationspeed = Game::config["spaceship.rotationSpeed"].as<float>();
	weaponCooldownToSet = Game::config["spaceship.weaponCooldown"].as<float>();
	friction = Game::config["spaceship.friction"].as<float>();
	lifes = Game::config["spaceship.lifes"].as<unsigned int>();
	hp = Game::config["spaceship.hp"].as<float>();
	bulletSpeed = Game::config["energyBullet.speed"].as<float>();

	thor::Resources::TextureKey key = thor::Resources::TextureKey::fromFile("res/ship.png"); //TODO needs exeption Handling
	texture = Game::textureManager.acquire(key);
    this->setTexture(*texture);
	this->setPosition(Game::getResolution().x/2.0f, Game::getResolution().y/2.0f);
	this->setOrigin(this->getLocalBounds().width/2.0f,this->getLocalBounds().height/2.0f);

	hitbox = rrr::loadHitbox("res/ship.col");
}

void Spaceship::update(float deltaTime) {

	if(spawnMode > 0.0f) {
		
		// move
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			this->move(0,200.0f*deltaTime);
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			this->move(0,200.0f*-deltaTime);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			this->move(200.0f*deltaTime,0);
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			this->move(200.0f*-deltaTime,0);

		spawnMode -= deltaTime; // reduce remaining time in spawn mode

		// blink to indicate spawn mode
		sf::Color color = this->getColor();
		if(spawnMode > 0.0f) {
			color.a -= int(400*deltaTime);
		} else {
			color.a = 255; // make sure that the spaceship is intransparent after spawn mode
		}
		this->setColor(color);
		

	} else {

		// rotate
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			this->rotate(rotationspeed*deltaTime);
		} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			this->rotate(-rotationspeed*deltaTime);
		}

		// set acceleration
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			acceleration[0] = -sin(this->getRotation()*(PI/180)) * -accelerationToSet;
			acceleration[1] = cos(this->getRotation()*(PI/180)) * -accelerationToSet;
		} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			acceleration[0] = -sin(this->getRotation()*(PI/180)) * accelerationToSet;
			acceleration[1] = cos(this->getRotation()*(PI/180)) * accelerationToSet;
		} else {
			// apply friction
			if(velocity[0] > 0) 
				acceleration[0] = -friction;
			else
				acceleration[0] = friction;
			if(velocity[1] > 0)
				acceleration[1] = -friction;
			else
				acceleration[1] = friction;
		}

		// accelerate
		velocity[0] += acceleration[0]*deltaTime;
		velocity[1] += acceleration[1]*deltaTime;

		// move
		this->move(velocity[0]*deltaTime, velocity[1]*deltaTime);
	
		// if the spaceship has left the field, set it to the opposite side
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

		// fire
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && (weaponCooldown <= 0)) {
			Singleplayer::entityManager.add(new EnergyBullet(
				sf::Vector2f(
					this->getPosition().x+sin(this->getRotation()*(PI/180))*this->getLocalBounds().width/2, // spawn the bullet in front of the shipt instead in the middle to prevent unwanted collisions
					this->getPosition().y-cos(this->getRotation()*(PI/180))*this->getLocalBounds().height/2),
				sqrt((velocity[0]*velocity[0])+(velocity[1]*velocity[1])) + bulletSpeed,
				this->getRotation()));
			weaponCooldown = weaponCooldownToSet;
		}
		weaponCooldown -= deltaTime;
	}
}

void Spaceship::takeDamage(float damage) {
	if(spawnMode <= 0.0f) { // not in spawn mode
		hp -= damage;
		if(hp <= 0) {
			// TODO destruction animation and respawn
			spawnMode = 2.0f;
			setRotation(0.0f);
			velocity[0] = 0.0f;
			velocity[1] = 0.0f;
			setPosition(Game::getResolution().x/2.0f,Game::getResolution().y/2.0f);
			if(lifes > 0) {
				--lifes;
			} else {
				// TODO Game over
			}
		}
	}
}

void Spaceship::collide(unsigned int id) {
	
}

void Spaceship::rcvMessage(unsigned int msg) {

}

void Spaceship::reset() {
	velocity[1] = 0;
	velocity[0] = 0;
	setPosition(Game::getResolution().x/2.0f,Game::getResolution().y/2.0f);
	setRotation(0.0f);
}