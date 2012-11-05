/**
* Copyright (c) 2012, Jens Mölzer
* This file is part of the asteroids project and is realeased under the BSD 2-Clause License.
* For more Details on licensing, see 'LICENCE.txt'.
**/

#pragma once

#include "Entity.hpp"
#include "EntityTypes.hpp"
#include <boost/any.hpp>
#include <SFML/System.hpp>
#include <Thor/Resources.hpp>

class DebrisChunk : public Entity {

public:
    DebrisChunk(EntityManager& manager, const std::shared_ptr<sf::Texture>& texture);
    
    DebrisChunk(EntityManager& manager, const sf::Vector2f& pos, const sf::Vector2f& velocity, const std::shared_ptr<sf::Texture>& texture);
    
    void update(float deltaTime);
    
    void collide(unsigned int id, unsigned int type) {}
    
    void rcvMessage(unsigned int msg, const std::vector<boost::any>& params = std::vector<boost::any>()) {}
    
    void reset() {}
    
    unsigned int getType() const { return EntityTypes::DEBRIS; }
    
    float getFadeSpeed() const { return fadeSpeed; }
    
    void setFadeSpeed(float speed) { fadeSpeed = speed; }

    bool isRunning() const { return running; }
    
    void setRunning(bool running) { this->running = running; }

private:
    bool running;
    float alpha;
    float fadeSpeed;
    std::shared_ptr<sf::Texture> texture;
    
};
