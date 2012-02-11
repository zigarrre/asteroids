#include "Singleplayer.hpp"

EntityManager Singleplayer::entityManager(10);

Singleplayer::Singleplayer(sf::RenderWindow& renderWindow) :
    renderWindow(renderWindow),
	initialized(false)
{
	texBackground = Game::textureManager.Acquire(thor::Resources::TextureKey::FromFile("res/background.png"));
	background.SetTexture(*texBackground);
	init();
}

void Singleplayer::init() {
	if(!initialized) {
		entityManager.add(new Spaceship(sf::Vector2f(20.0f,20.0f)), SPACESHIP);
		entityManager.add(new Asteroid(sf::Vector2f(0.0f,0.0f),sf::Vector2f(20.0f,30.0f),Asteroid::BIG));
	}
}

void Singleplayer::reinit() {
	entityManager.clear();
	initialized = false;
	init();
}

unsigned short Singleplayer::update(float deltaTime) {

    sf::Event e;
    while (renderWindow.PollEvent(e)) {
        if (e.Type == sf::Event::Closed)
            renderWindow.Close();
		else if (e.Type == sf::Event::KeyPressed && e.Key.Code == sf::Keyboard::Escape)
			return Game::MAIN_MENU;
		else if (e.Type == sf::Event::KeyPressed && e.Key.Code == sf::Keyboard::H)
			entityManager.showHitBox = !entityManager.showHitBox;
    }
	entityManager.update(deltaTime);
	hud.update(deltaTime);

	return Game::SINGLEPLAYER;
}

void Singleplayer::draw() {
	renderWindow.Draw(background);
	entityManager.draw(renderWindow);
	hud.draw(renderWindow);
}
