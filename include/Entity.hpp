#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>
#include "ConvexPolygon.hpp"

class Entity : public sf::Sprite
{
	friend class EntityManager;

    public:
        Entity();
		virtual ~Entity() {}
        virtual void update(float deltaTime) = 0;
		unsigned int getID() { return id; }
		sf::ConvexShape getHitBox() const;
		virtual void collide(unsigned int id) = 0;
		virtual void rcvMessage(unsigned int msg) = 0;
    protected:
        float velocity[2];
        float acceleration[2];
		unsigned int id;
		sf::ConvexShape hitbox;
    private:
};

#endif // ENTITY_HPP
