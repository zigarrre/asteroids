#pragma once

#include <SFML/Graphics.hpp>
#include <sstream>
#include <fstream>

const float PI = 3.1415926f;

namespace rrr {

	template <class T>
	std::string toString (const T& t) {
		std::stringstream ss;
		ss << t;
		return ss.str();
	}

	/// load a hitbox from a file
	/// hitbox has to be in this format:
	/// x1 y1
	/// x2 y2
	/// ...
	sf::ConvexShape loadHitbox(const std::string& path);

}
