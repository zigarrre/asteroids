#pragma once

#include "Point.hpp"
#include <vector>

class ConvexPolygon {

public:

	ConvexPolygon() : posX(0.0f), posY(0.0f) {}
	ConvexPolygon(float posX, float posY) : posX(posX), posY(posY) {}

    float posX, posY;
    std::vector<Point> points;
};
