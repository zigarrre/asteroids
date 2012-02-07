#include "GamestateManager.hpp"

using namespace std;

GamestateManager::GamestateManager() :
	activeState(0)
{
	
}

void GamestateManager::add(Gamestate* gamestate, unsigned short id) {
	gamestates.insert(pair<unsigned short,Gamestate*>(id, gamestate));
}

void GamestateManager::remove(unsigned short id) {
	delete gamestates[id];
	gamestates.erase(id);
}

void GamestateManager::clear() {
	map<unsigned short,Gamestate*>::iterator it = gamestates.begin();
	while(it != gamestates.end()) {
		delete it->second;
		it = gamestates.erase(it);
	}
}

void GamestateManager::update(float deltaTime) {
	activeState = gamestates[activeState]->update(deltaTime);
}