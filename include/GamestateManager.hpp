#pragma once

#include "Gamestate.hpp"
#include <map>

class GamestateManager {

public:
	GamestateManager();
	void add(Gamestate* gamestate, unsigned short id);
	void remove(unsigned short id);
	void clear();
	Gamestate* get(unsigned short id) { return gamestates[id]; }
	Gamestate* getActiveState() { return gamestates[activeState]; }
	unsigned short getActiveStateID() { return activeState; }
	void setActiveState(unsigned short id) { activeState = id; }
	void update(float deltaTime);

private:
	std::map<unsigned short, Gamestate*> gamestates;
	unsigned short activeState;

};