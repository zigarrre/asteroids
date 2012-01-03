#include "EntityManager.hpp"

using namespace std;

EntityManager::EntityManager(unsigned int reservedSpace) :
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
	entitys.erase(id);
}

unsigned int EntityManager::getNewID() {
	unsigned int i = reservedSpace;
	for(; entitys.count(i) != 0; ++i);
	return i;
}

void EntityManager::update(float deltaTime) {
	map<unsigned int,Entity*>::iterator it = entitys.begin();
	for(;it != entitys.end(); it++) {
		it->second->update(deltaTime);
	}
}

void EntityManager::draw(sf::RenderTarget& renderTarget) {
	map<unsigned int,Entity*>::iterator it = entitys.begin();
	for(;it != entitys.end(); it++) {
		renderTarget.Draw(*it->second);
	}
}