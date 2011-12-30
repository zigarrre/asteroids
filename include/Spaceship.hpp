#ifndef SPACESHIP_HPP
#define SPACESHIP_HPP

#include "include/Entity.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>


class Spaceship : public Entity
{
    public:
        Spaceship(const sf::Input& input, const sf::Image& img, const sf::Vector2f& pos);
        virtual void update(float deltaTime);
    protected:
    private:
        const sf::Input& input;
        float accelerationToSet;
};

#endif // SPACESHIP_HPP
