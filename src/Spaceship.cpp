#include "Spaceship.hpp"

Spaceship::Spaceship(const sf::Input& input, const sf::Image& img, const sf::Vector2f& pos) :
    input(input),
    accelerationToSet(1)
{
    this->SetImage(img);
    this->SetPosition(pos);
}

void Spaceship::update(float deltaTime) {
    velocity[0] += acceleration[0]*deltaTime;
    velocity[1] += acceleration[1]*deltaTime;
    if(input.IsKeyDown(sf::Key::Right)) {
        acceleration[0] = accelerationToSet;
    } else if(input.IsKeyDown(sf::Key::Left)) {
        acceleration[0] = accelerationToSet * -1;
    } else {
        acceleration[0] = 0;
    }
    if(input.IsKeyDown(sf::Key::Up)) {
        acceleration[1] = accelerationToSet;
    } else if (input.IsKeyDown(sf::Key::Down)) {
        acceleration[1] = accelerationToSet * -1;
    } else {
        acceleration[1] = 0;
    }
    this->Move(velocity[0], velocity[1]);
}
