#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <SFML/Graphics.hpp>

const int GAMESTATE_SINGLEPLAYER = 1;

class Gamestate {
    public:
        Gamestate() {}
        virtual ~Gamestate() {}
        virtual int update(float deltaTime) = 0;
        virtual void draw() = 0;
    protected:
    private:
};

#endif // GAMESTATE_HPP
