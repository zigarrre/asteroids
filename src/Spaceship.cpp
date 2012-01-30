#include "Spaceship.hpp"

using namespace std;

Spaceship::Spaceship(const sf::Vector2f& pos) :
    accelerationToSet(1.0f),
	rotationspeed(100.0f),
	weaponCooldown(0.0f),
	weaponCooldownToSet(0.5f),
	friction(0.05f)
{
	thor::Resources::TextureKey key = thor::Resources::TextureKey::FromFile("res/ship.png"); //TODO needs exeption Handling
	texture = Game::resourceManager.Acquire(key);
    this->SetTexture(*texture);
	this->SetPosition(Game::getResolution().x/2.0f, Game::getResolution().y/2.0f);
	this->SetOrigin(this->GetLocalBounds().Width/2.0f,this->GetLocalBounds().Height/2.0f);
	// define hitbox
	hitbox.SetPointCount(3);
	hitbox.SetPoint(0,sf::Vector2f(6.0f,41.0f));
	hitbox.SetPoint(1,sf::Vector2f(24.0f,8.0f));
	hitbox.SetPoint(2,sf::Vector2f(43.0f,41.0f));
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
    this->Move(velocity[0], velocity[1]);
	
	// if the spaceship has left the field, set it to the opposite side
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

	// fire
	if(sf::Keyboard::IsKeyPressed(sf::Keyboard::Space) && (weaponCooldown <= 0)) {
		Singleplayer::entityManager.add(new EnergyBullet(sf::Vector2f(this->GetPosition().x, this->GetPosition().y), this->GetRotation()));
		weaponCooldown = weaponCooldownToSet;
	}
	weaponCooldown -= deltaTime;
}

void Spaceship::collide(unsigned int id) {
	cout<<"collision"<<endl;
}

void Spaceship::rcvMessage(unsigned int msg) {

}