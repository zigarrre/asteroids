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
		hitbox.SetPointCount(lines);

		for(unsigned int i = 0; i < lines; ++i) {
			sf::Vector2f point;
			file>>point.x>>point.y;
			hitbox.SetPoint(i,point);
		}

		file.close();

		return hitbox;
	}

}