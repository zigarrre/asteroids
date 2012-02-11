#include "Spaceship.hpp"

using namespace std;

Spaceship::Spaceship(const sf::Vector2f& pos) :
    accelerationToSet(1.0f),
	rotationspeed(100.0f),
	weaponCooldown(0.0f),
	weaponCooldownToSet(0.5f),
	friction(0.05f),
	lifes(3),
	hp(1.0f),
	spawnMode(0.0f)
{
	thor::Resources::TextureKey key = thor::Resources::TextureKey::FromFile("res/ship.png"); //TODO needs exeption Handling
	texture = Game::textureManager.Acquire(key);
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

	if(spawnMode > 0.0f) {
		
		// move
		if(sf::Keyboard::IsKeyPressed(sf::Keyboard::Down))
			this->Move(0,200.0f*deltaTime);
		else if(sf::Keyboard::IsKeyPressed(sf::Keyboard::Up))
			this->Move(0,200.0f*-deltaTime);
		if(sf::Keyboard::IsKeyPressed(sf::Keyboard::Right))
			this->Move(200.0f*deltaTime,0);
		else if(sf::Keyboard::IsKeyPressed(sf::Keyboard::Left))
			this->Move(200.0f*-deltaTime,0);

		spawnMode -= deltaTime; // reduce remaining time in spawn mode

		// blink to indicate spawn mode
		sf::Color color = this->GetColor();
		if(spawnMode > 0.0f) {
			color.a -= int(400*deltaTime);
		} else {
			color.a = 255; // make sure that the spaceship is intransparent after spawn mode
		}
		this->SetColor(color);
		

	} else {

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
			Singleplayer::entityManager.add(new EnergyBullet(
				sf::Vector2f(
					this->GetPosition().x+sin(this->GetRotation()*(PI/180))*this->GetLocalBounds().Width/2, // spawn the bullet in front of the shipt instead in the middle to prevent unwanted collisions
					this->GetPosition().y-cos(this->GetRotation()*(PI/180))*this->GetLocalBounds().Height/2),
				this->GetRotation()));
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
			SetRotation(0.0f);
			velocity[0] = 0.0f;
			velocity[1] = 0.0f;
			SetPosition(Game::getResolution().x/2.0f,Game::getResolution().y/2.0f);
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
