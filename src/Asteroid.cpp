#include "Asteroid.hpp"

Asteroid::Asteroid(const sf::Vector2f& pos, const sf::Vector2f& velocity, float rotation, float rotationVelocity) :
	rotationVelocity(rotationVelocity),
	running(true),
	hp(1.0f)
{
	SetPosition(pos);
	SetOrigin(GetLocalBounds().Width/2,GetLocalBounds().Height/2);
	SetRotation(rotation);
	this->velocity[0] = velocity.x;
	this->velocity[1] = velocity.y;
	thor::Resources::TextureKey key = thor::Resources::TextureKey::FromFile("res/asteroid.png"); //TODO needs exeption Handling
	texture = Game::resourceManager.Acquire(key);
    this->SetTexture(*texture);
	hitbox.SetPointCount(7);
	hitbox.SetPoint(0,sf::Vector2f(18.0f,64.0f));
	hitbox.SetPoint(1,sf::Vector2f(49.0f,63.0f));
	hitbox.SetPoint(2,sf::Vector2f(78.0f,50.0f));
	hitbox.SetPoint(3,sf::Vector2f(79.0f,18.0f));
	hitbox.SetPoint(4,sf::Vector2f(51.0f,5.0f));
	hitbox.SetPoint(5,sf::Vector2f(19.4f,12.7f));
	hitbox.SetPoint(6,sf::Vector2f(5.0f,40.0f));
}

void Asteroid::update(float deltaTime) {
	if(running) {
		
		if(hp <= 0.0f) {
			// object destroid
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

}

void Asteroid::rcvMessage(unsigned int msg) {

}

void Asteroid::takeDamage(float damage) {
	hp -= damage;
}