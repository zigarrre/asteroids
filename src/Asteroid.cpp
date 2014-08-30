/**
* Copyright (c) 2012, Jens Mölzer
* This file is part of the asteroids project and is realeased under the BSD 2-Clause License.
* For more Details on licensing, see 'LICENCE.txt'.
**/

#include "Asteroid.hpp"
#include "Spaceship.hpp"
#include "Singleplayer.hpp"
#include "Messages.hpp"
#include "MessageSystem.hpp"
#include "DebrisChunk.hpp"

using namespace std;

int Asteroid::asteroidCount = 0;

Asteroid::Asteroid(EntityManager& manager, const sf::Vector2f& pos, const sf::Vector2f& velocity, unsigned short size, float rotation, float rotationVelocity) :
    Entity(manager),
    running(true),
    rotationVelocity(rotationVelocity),
    hp(1),
    size(size)
{
    // set config parameters
    hp = Game::getHandle().config["asteroid.hp"].as<int>();
    spread = Game::getHandle().config["asteroid.spread"].as<float>();
    spread *= (PI/180); // convert degree to radian

    // load resources
    if(size == BIG) {
        hitbox = rrr::loadHitbox("res/asteroid.col");
        texture = Game::getHandle().textureManager.acquire(thor::Resources::fromFile<sf::Texture>("res/asteroid.png"));
    } else if(size == MEDIUM) {
        hitbox = rrr::loadHitbox("res/asteroidMedium.col");
        texture = Game::getHandle().textureManager.acquire(thor::Resources::fromFile<sf::Texture>("res/asteroidMedium.png"));
    } else if(size == SMALL) {
        hitbox = rrr::loadHitbox("res/asteroidSmall.col");
        texture = Game::getHandle().textureManager.acquire(thor::Resources::fromFile<sf::Texture>("res/asteroidSmall.png"));
    }
    debrisTexture = Game::getHandle().textureManager.acquire(thor::Resources::fromFile<sf::Texture>("res/asteroidDebrisChunk.png"));

    // configure sprites and position
    this->setTexture(*texture);
    setOrigin(getLocalBounds().width/2,getLocalBounds().height/2);
    setPosition(pos);
    setRotation(rotation);
    this->velocity[0] = velocity.x;
    this->velocity[1] = velocity.y;

    ++asteroidCount;
}

void Asteroid::update(float deltaTime) {
    if(running) {
        
        if(hp <= 0) {
            MessageSystem::getHandle().sendMessage(EngineMessages::ASTEROID_DESTROYED);
            // object destroid
            if(size > SMALL) {
                sf::Vector2f newVelocity;
                newVelocity.x = velocity[0] * cos(spread) - velocity[1] * sin(spread);
                newVelocity.y = velocity[1] * cos(spread) + velocity[0] * sin(spread);
                Singleplayer::entityManager.add(new Asteroid(manager, getPosition(),newVelocity,size-1,getRotation(),rotationVelocity));
                newVelocity.x = velocity[0] * cos(spread) + velocity[1] * sin(spread);
                newVelocity.y = velocity[1] * cos(spread) - velocity[0] * sin(spread);
                Singleplayer::entityManager.add(new Asteroid(manager, getPosition(),newVelocity,size-1,getRotation(),rotationVelocity));
            }
            DebrisChunk::spawnDebris(manager, getPosition(), debrisTexture);
            Singleplayer::entityManager.remove(getID());
            return;
        }

        move(velocity[0]*deltaTime, velocity[1]*deltaTime);
        rotate(rotationVelocity*deltaTime);

        // if the astroid has left the field, set it to the opposite side
        sf::Vector2f pos = this->getPosition();
        sf::Vector2f size;
        size.x = this->getGlobalBounds().width;
        size.y = this->getGlobalBounds().height;
        if((pos.x + (size.x/2)) < 0) {
            this->setPosition(Game::getHandle().getResolution().x + (size.x/2), pos.y);
        } else if(pos.x - (size.x/2) > Game::getHandle().getResolution().x) {
            this->setPosition(-size.x+(size.x/2),pos.y);
        }
        if((pos.y + (size.y/2)) < 0) {
            this->setPosition(pos.x, Game::getHandle().getResolution().y + (size.y/2));
        } else if(pos.y - (size.y/2) > Game::getHandle().getResolution().y) {
            this->setPosition(pos.x, -size.y+(size.y/2));
        }
    }
}

void Asteroid::collide(unsigned int id, unsigned int type) {
    if(type == EntityTypes::SPACESHIP) {
        vector<boost::any> params;
        params.push_back(boost::any(int(1)));
        manager.sndMessage(id, Messages::TAKE_DAMAGE, params);
    }
}

void Asteroid::rcvMessage(unsigned int msg, const std::vector<boost::any>& params) {
    if(msg == Messages::TAKE_DAMAGE) {
        hp -= boost::any_cast<int>(params[0]);
    }
}
