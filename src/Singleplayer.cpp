#include "Singleplayer.hpp"

EntityManager Singleplayer::entityManager(10);

Singleplayer::Singleplayer(sf::RenderWindow& renderWindow) :
    renderWindow(renderWindow)
{
	entityManager.add(new Spaceship(sf::Vector2f(20.0f,20.0f)));
}

int Singleplayer::update(float deltaTime) {

    sf::Event Event;
    while (renderWindow.PollEvent(Event)) {
        if (Event.Type == sf::Event::Closed)
            renderWindow.Close();
    }
	entityManager.update(deltaTime);

    return GAMESTATE_SINGLEPLAYER;
}

void Singleplayer::draw() {
	entityManager.draw(renderWindow);
}
