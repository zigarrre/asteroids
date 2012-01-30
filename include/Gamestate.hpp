#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <SFML/Graphics.hpp>

class Gamestate {
    public:
        Gamestate() {}
        virtual ~Gamestate() {}
        virtual unsigned short update(float deltaTime) = 0;
        virtual void draw() = 0;
    protected:
    private:
};

#endif // GAMESTATE_HPP
