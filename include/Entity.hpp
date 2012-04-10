/**
* Copyright (c) 2012, Jens M�lzer
* This file is part of the asteroids project and is realeased under the BSD 2-Clause License.
* For more Details on licensing, see 'LICENCE.txt'.
**/

#pragma once

#include <SFML/Graphics.hpp>
#include "ConvexPolygon.hpp"

class Entity : public sf::Sprite
{
	friend class EntityManager;

    public:
        Entity(EntityManager& manager);
		virtual ~Entity() {}
        virtual void update(float deltaTime) = 0;
		unsigned int getID() { return id; }
		sf::ConvexShape getHitBox() const;
		virtual void collide(unsigned int id) = 0;
		virtual void rcvMessage(unsigned int msg) = 0;
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
