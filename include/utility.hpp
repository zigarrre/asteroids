#pragma once

#include <sstream>

const float PI = 3.1415926f;

namespace rrr {

	template <class T>
	std::string toString (const T& t) {
		std::stringstream ss;
		ss << t;
		return ss.str();
	}

}
