/**
* Copyright (c) 2012, Jens Mölzer
* This file is part of the asteroids project and is realeased under the BSD 2-Clause License.
* For more Details on licensing, see 'LICENCE.txt'.
**/

#pragma once

#include <SFML/Graphics.hpp>
#include <sstream>
#include <fstream>

const float PI = 3.1415926f;

namespace rrr {

	/**
	* cast objects supporting << to string (in general numbers like int, double, ...)
	**/
	template <class T>
	std::string toString(const T& t) {
		std::stringstream ss;
		ss << t;
		return ss.str();
	}

	/**
	* cast from string to objects supporting >> (in general numbers like int, double, ...)
	**/
	template <class T>
	T fromString(const std::string str) {
		std::istringstream iss;
		iss.str(str);
		T out;
		iss>>out;
		return out;
	}

	/// load a hitbox from a file
	/// hitbox has to be in this format:
	/// x1 y1
	/// x2 y2
	/// ...
	sf::ConvexShape loadHitbox(const std::string& path);

}
