/**
* Copyright (c) 2012, Jens Mölzer
* This file is part of the asteroids project and is realeased under the BSD 2-Clause License.
* For more Details on licensing, see 'LICENCE.txt'.
**/

#include "Highscore.hpp"
#include "utility.hpp"
#include <fstream>
#include <sstream>

using namespace std;

class BadIndexException : public exception {
};

Highscore::Highscore() :
    currentScore(0)
{
    scores = new HighscoreEntry[10];
    for(unsigned int i = 0; i < 10; ++i) {
        scores[i].name = "-";
        scores[i].score = 0;
    }
}

Highscore::~Highscore() {
    delete[] scores;
}

bool Highscore::loadFromFile(const std::string& path) {
    ifstream file;
    file.open(path);

    if(!file.good())
        return false;

    for(unsigned int i = 0; i < 10 && file.good(); ++i) {
        string line;
        getline(file, line);
        istringstream iss;
        iss.str(line);
        getline(iss, scores[i].name, ';');
        string score;
        getline(iss, score, ';');
        scores[i].score = rrr::fromString<unsigned int>(score);
    }

    file.close();

    return true;
}

bool Highscore::saveToFile(const std::string& path) const {
    ofstream file;
    file.open(path);

    if(!file.good())
        return false;

    for(unsigned int i = 0; i < 10; ++i) {
        file<<scores[i].name<<';'<<scores[i].score;
        if(i < 9)
            file<<'\n';
    }

    return true;
}

const HighscoreEntry& Highscore::operator[](unsigned int index) const {
    if(index > 9)
        throw(BadIndexException());
    else
        return scores[index];
}

bool Highscore::newHighscore() const{
    if(currentScore > scores[9].score)
        return true;
    else
        return false;
}

bool Highscore::saveCurrentScore(const std::string& name) {
    unsigned int pos = 10;
    while(currentScore > scores[pos-1].score && pos > 0) // find out where to insert new score
        --pos;
    
    if(pos > 9) // no new highscore
        return false;

    for(unsigned int i = 9; i > pos; --i) // move older scores one back
        scores[i] = scores[i-1];

    // insert new score
    scores[pos].name = name;
    scores[pos].score = currentScore;

    return true;
}