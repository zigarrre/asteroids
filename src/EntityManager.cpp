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

bool EntityManager::testSATCollision(ConvexPolygon poly1, ConvexPolygon poly2) {
	// save size in variable to improve performance
	unsigned int size1 = poly1.points.size();
	unsigned int size2 = poly2.points.size();

	Point side, projectionAxis;

	if((size1 == 0) || (size2 == 0)) {
		// no points defined in the polygons
		return false;
	}

	// for every side in poly1
	for(unsigned int i = 0; i < size1; ++i) {
		// calculate on side
		side = poly1.points[i] - poly1.points[(i+1)%size1];

		// create an perpendicular axis for projection from side
		projectionAxis.x = -side.y;
		projectionAxis.y = side.x;

		// normalize the axis
		float axisLenght = sqrt(projectionAxis.x * projectionAxis.x + projectionAxis.y * projectionAxis.y);
		projectionAxis.x /= axisLenght;
		projectionAxis.y /= axisLenght;

		// initialise variales with min and max values
		float poly1Min = std::numeric_limits<float>::max(), poly1Max = -poly1Min;
		float poly2Min = std::numeric_limits<float>::max(), poly2Max = -poly2Min;

		float projection;

		// project all points from poly1 on the projection axis and save the max and min values
		for(unsigned int i = 0; i < size1; ++i) {
			projection = (projectionAxis.x * (poly1.points[i].x + poly1.posX) + projectionAxis.y * (poly1.points[i].y + poly1.posY)) / (projectionAxis.x * projectionAxis.x + projectionAxis.y * projectionAxis.y);
			poly1Min = min(projection, poly1Min);
			poly1Max = max(projection, poly1Max);
		}

		// project all points from poly2 on the projection axis and save the max and min values
		for(unsigned int i = 0; i < size1; ++i) {
			projection = (projectionAxis.x * (poly2.points[i].x + poly2.posX) + projectionAxis.y * (poly2.points[i].y + poly2.posY)) / (projectionAxis.x * projectionAxis.x + projectionAxis.y * projectionAxis.y);
			poly2Min = min(projection, poly2Min);
			poly2Max = max(projection, poly2Max);
		}

		// check if the projections of the polygons overlap
		if(!(poly1Max >= poly2Max && poly1Min <= poly2Min))
			return false; // there is no collision and we can return now
	}

	// for every side in poly2
	for(unsigned int i = 0; i < size2; ++i) {
		// calculate on side
		side = poly2.points[i] - poly2.points[(i+1)%size1];

		// create an perpendicular axis for projection from side
		projectionAxis.x = -side.y;
		projectionAxis.y = side.x;

		// normalize the axis
		float axisLenght = sqrt(projectionAxis.x * projectionAxis.x + projectionAxis.y * projectionAxis.y);
		projectionAxis.x /= axisLenght;
		projectionAxis.y /= axisLenght;

		// initialise variales with min and max values
		float poly1Min = std::numeric_limits<float>::max(), poly1Max = -poly1Min;
		float poly2Min = std::numeric_limits<float>::max(), poly2Max = -poly2Min;

		float projection;

		// project all points from poly1 on the projection axis and save the max and min values
		for(unsigned int i = 0; i < size1; ++i) {
			projection = (projectionAxis.x * (poly1.points[i].x + poly1.posX) + projectionAxis.y * (poly1.points[i].y + poly1.posY)) / (projectionAxis.x * projectionAxis.x + projectionAxis.y * projectionAxis.y);
			poly1Min = min(projection, poly1Min);
			poly1Max = max(projection, poly1Max);
		}

		// project all points from poly2 on the projection axis and save the max and min values
		for(unsigned int i = 0; i < size1; ++i) {
			projection = (projectionAxis.x * (poly2.points[i].x + poly2.posX) + projectionAxis.y * (poly2.points[i].y + poly2.posY)) / (projectionAxis.x * projectionAxis.x + projectionAxis.y * projectionAxis.y);
			poly2Min = min(projection, poly2Min);
			poly2Max = max(projection, poly2Max);
		}

		// check if the projections of the polygons overlap
		if(!(poly1Max >= poly2Max && poly1Min <= poly2Min))
			return false; // there is no collision and we can return now
	}

}
