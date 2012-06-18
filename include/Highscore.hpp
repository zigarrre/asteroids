#pragma once

#include <string>

/**
* Helper class for class Highscore, represents a single entry in the highscore table
**/
class HighscoreEntry {
public:
	unsigned int score;
	std::string name;
};

/**
* Class to handle the highscore table
* Handles also the current score
**/
class Highscore {

public:
	Highscore();
	~Highscore();

	/**
	* Loads the scores from the specified file. If file can't be read false is returned and a new empty higscore table initialisied.
	* If everythinh is OK fals is returned.
	**/
	bool loadFromFile(const std::string& path);

	/**
	* Saves the scores to the specified file. If an error occures false is returned else true.
	**/
	bool saveToFile(const std::string& path) const;

	unsigned int getCurrentScore() const { return currentScore; }
	
	void resetCurrentScore() { currentScore = 0; }

	Highscore& operator+=(unsigned int a) { currentScore += a; }

	/**
	* Returnes the Score object for the specified place.
	* Counting starts with zero.
	* Only values from 0-9 are allowed (only the 10 best scores are saved).
	**/
	const HighscoreEntry& operator[](unsigned int index) const;

	/**
	* Returnes true if the current score is a new highscore.
	**/
	bool newHighscore() const;

	/**
	* Save current score as highscore. If the current score is worse than the worst highscore it is not saved.
	* If the current score is better than the worst highscore and saved true is returned.
	* The scores are NOT writen to disk. This function modifies only the RAM call saveToFile afterwards to save scores to disk.
	**/
	bool saveCurrentScore(const std::string& name);

private:
	unsigned int currentScore;
	HighscoreEntry* scores;

};