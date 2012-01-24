#pragma once

struct Point {
public:
	Point() : x(0), y(0) {}
	Point(float x, float y) : x(x), y(y) {}

	const Point operator+(const Point& rhs) const {
		return Point(x + rhs.x, y + rhs.y);
	}

	const Point operator-(const Point& rhs) const {
		return Point(x - rhs.x, y - rhs.y);
	}

	Point& operator+=(const Point& rhs) {
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	Point& operator-=(const Point& rhs) {
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}

	float x,y;
};