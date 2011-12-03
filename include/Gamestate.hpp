#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <SFML/Graphics.hpp>

class Gamestate {
    public:
        Gamestate() {}
        virtual ~Gamestate() {}
        int void update(float deltaTime) = 0;
        virtual void draw(sf::RenderTarget& renderTarget) = 0;
    protected:
    private:
};

#endif // GAMESTATE_HPP
