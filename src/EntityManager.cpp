/**
* Copyright (c) 2012, Jens M�lzer
* This file is part of the asteroids project and is realeased under the BSD 2-Clause License.
* For more Details on licensing, see 'LICENCE.txt'.
**/

#include "EntityManager.hpp"

using namespace std;

EntityManager::EntityManager(unsigned int reservedSpace) :
	showHitBox(false),
	reservedSpace(reservedSpace)
{
}

EntityManager::~EntityManager() {}

unsigned int EntityManager::add(Entity* entity) {
	entity->id = getNewID();
	if(entitys.insert(pair<int,Entity*>(entity->getID(),entity)).second == false) {
		// element allready existent
		return 0;
	} else {
		return entity->getID();
	}
}

void EntityManager::add(Entity* entity, unsigned int id) {
	entity->id = id;
	if(entitys.insert(pair<int,Entity*>(entity->getID(),entity)).second == false) {
		// element allready existent
	}
}

void EntityManager::remove(unsigned int id) {
	delete entitys[id];
	entitys[id] = 0;
}

unsigned int EntityManager::getNewID() {
	unsigned int i = reservedSpace;
	for(; entitys.count(i) != 0; ++i);
	return i;
}

void EntityManager::update(float deltaTime) {
	map<unsigned int,Entity*>::iterator it = entitys.begin();
	// update elements
	while(it != entitys.end()) {
		it->second->update(deltaTime);
		// remove element if entity is deleted (pointer set to 0)
		if(it->second != 0) {
			++it;
		} else {
			it = entitys.erase(it); // erase returns next valid element
		}
	}
	// check for collisions
	it = entitys.begin();
	for(;it != entitys.end();++it) {
		// set it2 to the next element after it because we've checked the combinations before it allready
		map<unsigned int,Entity*>::iterator it2 = it;
		++it2;
		for(;it2 != entitys.end();++it2) {
			if(it != it2 && testSATCollision(it2->second->getHitBox(),it->second->getHitBox())) {
				it->second->collide(it2->second->getID());
				it2->second->collide(it->second->getID());
			}
		}
	}
}

void EntityManager::draw(sf::RenderTarget& renderTarget) {
	map<unsigned int,Entity*>::iterator it = entitys.begin();
	for(;it != entitys.end(); it++) {
		renderTarget.draw(*it->second);
		if(showHitBox)
			renderTarget.draw(it->second->getHitBox());
	}
}

void EntityManager::clear() {
	map<unsigned int,Entity*>::iterator it = entitys.begin();
	while(it != entitys.end()) {
		delete it->second;
		it = entitys.erase(it);
	}
}

bool EntityManager::testSATCollision(const sf::ConvexShape& poly1, const sf::ConvexShape& poly2) {
    
    if((poly1.getPointCount() == 0) || (poly2.getPointCount() == 0)) {
		// no points defined in the polygons
		return false;
	}

    return sat(poly2, poly1) && sat(poly1, poly2);
}

bool EntityManager::sat(const sf::ConvexShape& poly1, const sf::ConvexShape& poly2) {
    // save size in variable to improve performance
	unsigned int size1 = poly1.getPointCount();
	unsigned int size2 = poly2.getPointCount();

    // for every side in poly1
	for(unsigned int i = 0; i < size1; ++i) {
		// calculate one side
		sf::Vector2f side = poly1.getPoint(i) - poly1.getPoint((i+1)%size1);

		// create an perpendicular axis for projection from side
        sf::Vector2f projectionAxis(-side.y, side.x);

		// normalize the axis
		float axisLenght = sqrt(projectionAxis.x * projectionAxis.x + projectionAxis.y * projectionAxis.y);
		projectionAxis.x /= axisLenght;
		projectionAxis.y /= axisLenght;

		// initialise variables with min and max values
		float poly1Min = std::numeric_limits<float>::max(), poly1Max = -poly1Min;
		float poly2Min = std::numeric_limits<float>::max(), poly2Max = -poly2Min;

		// project all points from poly1 on the projection axis and save the max and min values
		for(unsigned int j = 0; j < size1; ++j) {
			float projection = (projectionAxis.x * poly1.getTransform().transformPoint(poly1.getPoint(j)).x + projectionAxis.y * poly1.getTransform().transformPoint(poly1.getPoint(j)).y) / (projectionAxis.x * projectionAxis.x + projectionAxis.y * projectionAxis.y);
			poly1Min = min(projection, poly1Min);
			poly1Max = max(projection, poly1Max);
		}

		// project all points from poly2 on the projection axis and save the max and min values
		for(unsigned int j = 0; j < size2; ++j) {
			float projection = (projectionAxis.x * poly2.getTransform().transformPoint(poly2.getPoint(j)).x + projectionAxis.y * poly2.getTransform().transformPoint(poly2.getPoint(j)).y) / (projectionAxis.x * projectionAxis.x + projectionAxis.y * projectionAxis.y);
			poly2Min = min(projection, poly2Min);
			poly2Max = max(projection, poly2Max);
		}

		// check if the projections of the polygons overlap
        if(!(poly1Max >= poly2Min && poly1Min <= poly2Max)) {
			return false; // there is no collision and we can return now
		}
	}
    
    return true; // all projections overlap, there is a collision
}

void EntityManager::sndMessage(unsigned int id, unsigned int msg) {
	entitys[id]->rcvMessage(msg);
}

void EntityManager::broadcastMessage(unsigned int msg) {
	map<unsigned int,Entity*>::iterator it = entitys.begin();
	for(;it != entitys.end(); it++) {
		it->second->rcvMessage(msg);
	}
}

Entity* EntityManager::getEntity(unsigned int id) {
	return entitys[id];
}