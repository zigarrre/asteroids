#include "Spaceship.hpp"

const float Spaceship::PI = 3.141592f;

Spaceship::Spaceship(const sf::Texture& tex, const sf::Vector2f& pos) :
    accelerationToSet(1.0f),
	rotationspeed(100.0f)
{
    this->SetTexture(tex);
    this->SetPosition(pos);
	this->SetOrigin(this->GetLocalBounds().Width/2.0f,this->GetLocalBounds().Height/2.0f);
}

void Spaceship::update(float deltaTime) {

	// rotate
	if(sf::Keyboard::IsKeyPressed(sf::Keyboard::Right)) {
		this->Rotate(rotationspeed*deltaTime);
	} else if(sf::Keyboard::IsKeyPressed(sf::Keyboard::Left)) {
		this->Rotate(-rotationspeed*deltaTime);
	}

	// set acceleration
	if(sf::Keyboard::IsKeyPressed(sf::Keyboard::Up)) {
		acceleration[0] = -sin(this->GetRotation()*(PI/180)) * -accelerationToSet;
		acceleration[1] = cos(this->GetRotation()*(PI/180)) * -accelerationToSet;
	} else if(sf::Keyboard::IsKeyPressed(sf::Keyboard::Down)) {
		acceleration[0] = -sin(this->GetRotation()*(PI/180)) * accelerationToSet;
		acceleration[1] = cos(this->GetRotation()*(PI/180)) * accelerationToSet;
	} else {
		acceleration[0] = 0;
		acceleration[1] = 0;
	}

	// accelerate
	velocity[0] += acceleration[0]*deltaTime;
    velocity[1] += acceleration[1]*deltaTime;

	// move
    this->Move(velocity[0], velocity[1]);

}
