/**
* Copyright (c) 2012, Jens Mölzer
* This file is part of the asteroids project and is realeased under the BSD 2-Clause License.
* For more Details on licensing, see 'LICENCE.txt'.
**/

#if !defined(_WIN32) && (defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__)))
    #define UNIX
#elif defined(_WIN64) || defined(_WIN32)
    #define WIN
#endif

#include "utility.hpp"

using namespace std;

namespace rrr {

	sf::ConvexShape loadHitbox(const string& path) {

		ifstream file;
		file.open(path);

		// get line count
		unsigned int lines = 1;
		while(file.good()) {
			if(file.get() == '\n')
				++lines;
		}
		
		// TODO reset read-pointer to begin instead of close and reopen the file
		file.close();
		file.open(path);

		sf::ConvexShape hitbox;
		hitbox.setPointCount(lines);

		for(unsigned int i = 0; i < lines; ++i) {
			sf::Vector2f point;
			file>>point.x>>point.y;
			hitbox.setPoint(i,point);
		}

		file.close();

		return hitbox;
	}

    std::string getHomePath() {
        #if defined(WIN)
            return std::getenv("APPDATA");
        #elif defined(UNIX)
            return std::getenv("HOME");
        #endif
    }

}