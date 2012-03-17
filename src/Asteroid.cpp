/**
* Copyright (c) 2012, Jens M�lzer
* This file is part of the asteroids project and is realeased under the BSD 2-Clause License.
* For more Details on licensing, see 'LICENCE.txt'.
**/

#include "Asteroid.hpp"
#include "Spaceship.hpp"
#include "Singleplayer.hpp"

int Asteroid::asteroidCount = 0;

Asteroid::Asteroid(const sf::Vector2f& pos, const sf::Vector2f& velocity, unsigned short size, float rotation, float rotationVelocity) :
	rotationVelocity(rotationVelocity),
	running(true),
	hp(1.0f),
	size(size)
{
	hp = Game::config["asteroid.hp"].as<float>();
	spread = Game::config["asteroid.spread"].as<float>();
	spread *= (PI/180); // convert degree to radian

	if(size == BIG) {
		hitbox = rrr::loadHitbox("res/asteroid.col");
		texture = Game::textureManager.Acquire(thor::Resources::TextureKey::FromFile("res/asteroid.png"));
	} else if(size == MEDIUM) {
		hitbox = rrr::loadHitbox("res/asteroidMedium.col");
		texture = Game::textureManager.Acquire(thor::Resources::TextureKey::FromFile("res/asteroidMedium.png"));
	} else if(size == SMALL) {
		hitbox = rrr::loadHitbox("res/asteroidSmall.col");
		texture = Game::textureManager.Acquire(thor::Resources::TextureKey::FromFile("res/asteroidSmall.png"));
	}
    this->SetTexture(*texture);

	SetOrigin(GetLocalBounds().Width/2,GetLocalBounds().Height/2);
	SetPosition(pos);
	SetRotation(rotation);
	this->velocity[0] = velocity.x;
	this->velocity[1] = velocity.y;

	++asteroidCount;
}

void Asteroid::update(float deltaTime) {
	if(running) {
		
		if(hp <= 0.0f) {
			// object destroid
			if(size > SMALL) {
				sf::Vector2f newVelocity;
				newVelocity.x = velocity[0] * cos(spread) - velocity[1] * sin(spread);
				newVelocity.y = velocity[1] * cos(spread) + velocity[0] * sin(spread);
				Singleplayer::entityManager.add(new Asteroid(GetPosition(),newVelocity,size-1,GetRotation(),rotationVelocity));
				newVelocity.x = velocity[0] * cos(spread) + velocity[1] * sin(spread);
				newVelocity.y = velocity[1] * cos(spread) - velocity[0] * sin(spread);
				Singleplayer::entityManager.add(new Asteroid(GetPosition(),newVelocity,size-1,GetRotation(),rotationVelocity));
			}
			Singleplayer::entityManager.remove(getID());
			return;
		}

		Move(velocity[0]*deltaTime, velocity[1]*deltaTime);
		Rotate(rotationVelocity*deltaTime);

		// if the astroid has left the field, set it to the opposite side
		sf::Vector2f pos = this->GetPosition();
		sf::Vector2f size;
		size.x = this->GetGlobalBounds().Width;
		size.y = this->GetGlobalBounds().Height;
		sf::Vector2f origin = this->GetOrigin();
		if((pos.x + (size.x/2)) < 0) {
			this->SetPosition(Game::getResolution().x + (size.x/2), pos.y);
		} else if(pos.x - (size.x/2) > Game::getResolution().x) {
			this->SetPosition(-size.x+(size.x/2),pos.y);
		}
		if((pos.y + (size.y/2)) < 0) {
			this->SetPosition(pos.x, Game::getResolution().y + (size.y/2));
		} else if(pos.y - (size.y/2) > Game::getResolution().y) {
			this->SetPosition(pos.x, -size.y+(size.y/2));
		}
	}
}

void Asteroid::collide(unsigned int id) {
	Spaceship* spaceship = dynamic_cast<Spaceship*>(Singleplayer::entityManager.getEntity(id));
	if(spaceship) {
		spaceship->takeDamage(1.0f);
	}
}

void Asteroid::rcvMessage(unsigned int msg) {

}

void Asteroid::takeDamage(float damage) {
	hp -= damage;
}