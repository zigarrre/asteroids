/**
* Copyright (c) 2012, Jens Mölzer
* This file is part of the asteroids project and is realeased under the BSD 2-Clause License.
* For more Details on licensing, see 'LICENCE.txt'.
**/

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
