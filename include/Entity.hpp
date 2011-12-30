#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>


class Entity : public sf::Sprite
{
    public:
        Entity();
        virtual void update(float deltaTime) = 0;
    protected:
        float velocity[2];
        float acceleration[2];
    private:
};

#endif // ENTITY_HPP
