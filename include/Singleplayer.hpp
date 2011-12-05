#ifndef SINGLEPLAYERGAME_HPP
#define SINGLEPLAYERGAME_HPP

#include "include/Gamestate.hpp"
#include <SFML/Graphics.hpp>


class Singleplayer : public Gamestate
{
    public:
        Singleplayer();
        virtual int update(float deltaTime);
        virtual void draw(sf::RenderTarget& renderTarget);
    protected:
    private:

};

#endif // SINGLEPLAYERGAME_HPP
