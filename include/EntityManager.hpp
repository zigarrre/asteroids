#pragma once

#include "Entity.hpp"
#include "ConvexPolygon.hpp"
#include <SFML/Graphics.hpp>
#include <map>

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
	void sndMessage(unsigned int id, unsigned int msg);
	void broadcastMessage(unsigned int msg);

private:
	std::map<unsigned int,Entity*> entitys;
	unsigned int getNewID();
	bool testSATCollision(sf::ConvexShape poly1, sf::ConvexShape poly2);

	unsigned int reservedSpace;

};