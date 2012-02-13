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
	SetPosition(pos);
	SetOrigin(GetLocalBounds().Width/2,GetLocalBounds().Height/2);
	SetRotation(rotation);
	this->velocity[0] = velocity.x;
	this->velocity[1] = velocity.y;
	// TODO crete only the key which is needed, but TextureKey has no constructor
	thor::Resources::TextureKey keyBig = thor::Resources::TextureKey::FromFile("res/asteroid.png"); //TODO needs exeption Handling
	thor::Resources::TextureKey keyMedium = thor::Resources::TextureKey::FromFile("res/asteroidMedium.png");
	thor::Resources::TextureKey keySmall = thor::Resources::TextureKey::FromFile("res/asteroidSmall.png");
	if(size == BIG) {
		hitbox.SetPointCount(7);
		hitbox.SetPoint(0,sf::Vector2f(18.0f,64.0f));
		hitbox.SetPoint(1,sf::Vector2f(49.0f,63.0f));
		hitbox.SetPoint(2,sf::Vector2f(78.0f,50.0f));
		hitbox.SetPoint(3,sf::Vector2f(79.0f,18.0f));
		hitbox.SetPoint(4,sf::Vector2f(51.0f,5.0f));
		hitbox.SetPoint(5,sf::Vector2f(19.4f,12.7f));
		hitbox.SetPoint(6,sf::Vector2f(5.0f,40.0f));
		texture = Game::textureManager.Acquire(keyBig);
	} else if(size == MEDIUM) {
		hitbox.SetPointCount(10);
		hitbox.SetPoint(0,sf::Vector2f(6.1f,32.5f));
		hitbox.SetPoint(1,sf::Vector2f(3.0f,23.9f));
		hitbox.SetPoint(2,sf::Vector2f(4.0f,14.7f));
		hitbox.SetPoint(3,sf::Vector2f(9.3f,6.6f));
		hitbox.SetPoint(4,sf::Vector2f(24.0f,3.1f));
		hitbox.SetPoint(5,sf::Vector2f(34.4f,5.5f));
		hitbox.SetPoint(6,sf::Vector2f(41.5f,12.4f));
		hitbox.SetPoint(7,sf::Vector2f(43.7f,25.8f));
		hitbox.SetPoint(8,sf::Vector2f(33.3f,33.6f));
		hitbox.SetPoint(9,sf::Vector2f(16.0f,36.3f));
		texture = Game::textureManager.Acquire(keyMedium);
	} else if(size == SMALL) {
		hitbox.SetPointCount(5);
		hitbox.SetPoint(0,sf::Vector2f(3.0f,15.7f));
		hitbox.SetPoint(1,sf::Vector2f(9.2f,4.1f));
		hitbox.SetPoint(2,sf::Vector2f(20.9f,3.1f));
		hitbox.SetPoint(3,sf::Vector2f(20.9f,13.8f));
		hitbox.SetPoint(4,sf::Vector2f(15.6f,17.7f));
		texture = Game::textureManager.Acquire(keySmall);
	}
    this->SetTexture(*texture);
	++asteroidCount;
}

void Asteroid::update(float deltaTime) {
	if(running) {
		
		if(hp <= 0.0f) {
			// object destroid
			if(size > SMALL) {
				Singleplayer::entityManager.add(new Asteroid(GetPosition(),sf::Vector2f(velocity[0]-10,velocity[1]+10),size-1,GetRotation(),rotationVelocity));
				Singleplayer::entityManager.add(new Asteroid(GetPosition(),sf::Vector2f(velocity[0]+10,velocity[1]-10),size-1,GetRotation(),rotationVelocity));
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