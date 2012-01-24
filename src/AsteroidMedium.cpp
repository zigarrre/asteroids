#include "AsteroidMedium.hpp"

AsteroidMedium::AsteroidMedium(const sf::Vector2f& pos, const sf::Vector2f& velocity, float rotation, float rotationVelocity) :
	rotationVelocity(rotationVelocity),
	running(true)
{
	SetPosition(pos);
	SetOrigin(GetLocalBounds().Width/2,GetLocalBounds().Height/2);
	SetRotation(rotation);
	this->velocity[0] = velocity.x;
	this->velocity[1] = velocity.y;
	thor::Resources::TextureKey key = thor::Resources::TextureKey::FromFile("res/asteroidMedium.png"); //TODO needs exeption Handling
	texture = Game::resourceManager.Acquire(key);
    this->SetTexture(*texture);
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
}

void AsteroidMedium::update(float deltaTime) {
	if(running) {

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

void AsteroidMedium::collide(unsigned int id) {

}

void AsteroidMedium::rcvMessage(unsigned int msg) {

}