#include "EnergyBullet.hpp"

EnergyBullet::EnergyBullet(const sf::Vector2f& pos, float angle) :
	running(true),
	speed(200.0f),
	timeToLive(2.0f)
{
	thor::Resources::TextureKey key = thor::Resources::TextureKey::FromFile("res/bullet1.png"); //TODO needs exeption Handling
	texture = Game::resourceManager.Acquire(key);
    this->SetTexture(*texture);
	this->SetOrigin(this->GetLocalBounds().Width/2.0f,this->GetLocalBounds().Height/2.0f);
	this->SetPosition(pos);
	this->SetRotation(angle);
	velocity[0] = speed * sin(angle*(PI/180));
	velocity[1] = speed * -cos(angle*(PI/180));
}

void EnergyBullet::update(float deltaTime) {
	if(running) {
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

		//Time to Live
		if(timeToLive <= 0) {
			Singleplayer::entityManager.remove(this->getID());
		} else {
			timeToLive -= deltaTime;
		}
	}
}