#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <SFML/Graphics.hpp>

enum Gamestates {
	SINGLEPLAYER,
	MAIN_MENU
};

class Gamestate {
    public:
        Gamestate() {}
        virtual ~Gamestate() {}
        virtual Gamestates update(float deltaTime) = 0;
        virtual void draw() = 0;
    protected:
    private:
};

#endif // GAMESTATE_HPP
