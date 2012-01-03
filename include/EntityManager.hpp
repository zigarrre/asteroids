#pragma once

#include "Entity.hpp"
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
	void remove(unsigned int id);
	void draw(sf::RenderTarget& renderTarget);

private:
	std::map<unsigned int,Entity*> entitys;
	unsigned int getNewID();

	unsigned int reservedSpace;

};