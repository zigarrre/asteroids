/**
* Copyright (c) 2012, Jens Mölzer
* This file is part of the asteroids project and is realeased under the BSD 2-Clause License.
* For more Details on licensing, see 'LICENCE.txt'.
**/

#pragma once

#include "ConvexPolygon.hpp"
#include <SFML/Graphics.hpp>
#include <boost/any.hpp>
#include <vector>

class Entity : public sf::Sprite
{
    friend class EntityManager;

    public:
        Entity(EntityManager& manager);
        virtual ~Entity() {}
        virtual void update(float deltaTime) = 0;
        unsigned int getID() { return id; }
        sf::ConvexShape getHitBox() const;
        virtual void collide(unsigned int id, unsigned int type) = 0;
        virtual void rcvMessage(unsigned int msg, const std::vector<boost::any>& params = std::vector<boost::any>()) = 0;
        virtual void reset() = 0;
        virtual unsigned int getType() const = 0;

    protected:
        float velocity[2];
        float acceleration[2];
        unsigned int id;
        sf::ConvexShape hitbox;
        EntityManager& manager;

    private:
};
