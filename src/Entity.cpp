#include "Entity.hpp"

Entity::Entity()
{
    velocity[0] = 0;
    velocity[1] = 0;
    acceleration[0] = 0;
    acceleration[0] = 0;
}

sf::ConvexShape Entity::getHitBox() const {
	sf::ConvexShape rv = hitbox;
	rv.SetOrigin(GetOrigin());
	rv.SetRotation(GetRotation());
	rv.SetPosition(GetPosition());
	return rv;
}