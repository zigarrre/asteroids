#include "EnergyBullet.hpp"

EnergyBullet::EnergyBullet(const sf::Vector2f& pos, float angle) :
	running(true),
	speed(200.0f),
	timeToLive(3.0f),
	destroyed(false)
{
	thor::Resources::TextureKey key = thor::Resources::TextureKey::FromFile("res/bullet1.png"); //TODO needs exeption Handling
	texture = Game::textureManager.Acquire(key);
    this->SetTexture(*texture);
	this->SetOrigin(this->GetLocalBounds().Width/2.0f,this->GetLocalBounds().Height/2.0f);
	this->SetPosition(pos);
	this->SetRotation(angle);
	velocity[0] = speed * sin(angle*(PI/180));
	velocity[1] = speed * -cos(angle*(PI/180));
	hitbox.SetPointCount(4);
	hitbox.SetPoint(0,sf::Vector2f(7.0f,17.0f));
	hitbox.SetPoint(1,sf::Vector2f(7.0f,2.0f));
	hitbox.SetPoint(2,sf::Vector2f(12.0f,2.0f));
	hitbox.SetPoint(3,sf::Vector2f(12.0f,17.0f));
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
		this->Move(velocity[0] * deltaTime, velocity[1] * deltaTime);

		// if the bullet has left the field, set it to the opposite side
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

void EnergyBullet::collide(unsigned int id) {
	Asteroid* asteroid = dynamic_cast<Asteroid*>(Singleplayer::entityManager.getEntity(id));
	if(asteroid) {
		//cast ok
		asteroid->takeDamage(1.0f);
	}
	destroyed = true;
}

void EnergyBullet::rcvMessage(unsigned int msg) {

}