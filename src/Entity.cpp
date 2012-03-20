/**
* Copyright (c) 2012, Jens Mölzer
* This file is part of the asteroids project and is realeased under the BSD 2-Clause License.
* For more Details on licensing, see 'LICENCE.txt'.
**/

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
	rv.setOrigin(getOrigin());
	rv.setRotation(getRotation());
	rv.setPosition(getPosition());
	return rv;
}