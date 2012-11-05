/**
* Copyright (c) 2012, Jens Mölzer
* This file is part of the asteroids project and is realeased under the BSD 2-Clause License.
* For more Details on licensing, see 'LICENCE.txt'.
**/

#include "DebrisChunk.hpp"
#include "Game.hpp"
#include "EntityManager.hpp"
#include <cmath>

DebrisChunk::DebrisChunk(EntityManager& manager, const std::shared_ptr<sf::Texture>& texture) :
    DebrisChunk(manager, sf::Vector2f(0.0f,0.0f), sf::Vector2f(0.0f,0.0f), texture)
{
}

DebrisChunk::DebrisChunk(EntityManager& manager, const sf::Vector2f& pos, const sf::Vector2f& velocity, const std::shared_ptr<sf::Texture>& texture):
    Entity(manager),
    running(false),
    alpha(255.0f),
    fadeSpeed(255.0f),
    texture(texture)
{
    this->setPosition(pos);
    this->velocity[0] = velocity.x;
    this->velocity[1] = velocity.y;
    this->setTexture(*texture);
}

void DebrisChunk::update(float deltaTime) {
    move(velocity[0]*deltaTime, velocity[1]*deltaTime);
    if(alpha > 0.0f) {
        alpha -= fadeSpeed * deltaTime;
        setColor(sf::Color(255,255,255,round(alpha)));
    } else {
        manager.remove(getID());
    }
}

