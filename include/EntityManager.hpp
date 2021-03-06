/**
* Copyright (c) 2012, Jens Mölzer
* This file is part of the asteroids project and is realeased under the BSD 2-Clause License.
* For more Details on licensing, see 'LICENCE.txt'.
**/

#pragma once

#include "Entity.hpp"
#include "ConvexPolygon.hpp"
#include <SFML/Graphics.hpp>
#include <map>
#include <vector>
#include <boost/any.hpp>

class EntityManager {

public:
	// everything from 0 to < reservedSpace is reserved for manual assigned ids, everything above for automatic assigned ids
	EntityManager(unsigned int reservedSpace = 10);
	~EntityManager();
	void update(float deltaTime);
	// add an entity with an automatically at runtime generated id
	unsigned int add(Entity* entity);
	// add an entity with the given id
	void add(Entity* entity, unsigned int id);
	Entity* getEntity(unsigned int id);
	void remove(unsigned int id);
	void draw(sf::RenderTarget& renderTarget);
	void clear();

	/**
	* Sends a message to the specified entity
	*
	* id: the ID of the entity which should receive the message
	* msg: the type of the message (see Messages.hpp for definition of Message Types)
	* params: the parameters needed to process the message. For details about which messages have which parameters, see definition in Messages.hpp.
	**/
	void sndMessage(unsigned int id, unsigned int msg, const std::vector<boost::any>& params = std::vector<boost::any>());

	/**
	* Sends a message to all entities
	*
	* msg: the type of the message (see Messages.hpp for definition of Message Types)
	* params: the parameters needed to process the message. For details about which messages have which parameters, see definition in Messages.hpp.
	**/
	void broadcastMessage(unsigned int msg, const std::vector<boost::any>& params = std::vector<boost::any>());

	bool showHitBox;

private:
	std::map<unsigned int,Entity*> entitys;
	unsigned int getNewID();
	bool testSATCollision(const sf::ConvexShape& poly1, const sf::ConvexShape& poly2);

	/**
	* Helper function for testSATCollision. Tests the sides of one convex polygon for Collisions
	* Has to be call two times with the same polygons in inverted order to be sure that there is a collision
	**/
	bool sat(const sf::ConvexShape& poly1, const sf::ConvexShape& poly2);

	unsigned int reservedSpace;

};