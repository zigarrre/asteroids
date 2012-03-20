/**
* Copyright (c) 2012, Jens Mölzer
* This file is part of the asteroids project and is realeased under the BSD 2-Clause License.
* For more Details on licensing, see 'LICENCE.txt'.
**/

#include "Singleplayer.hpp"

#include <iostream>
using namespace std;

EntityManager Singleplayer::entityManager(10);

Singleplayer::Singleplayer(sf::RenderWindow& renderWindow) :
    renderWindow(renderWindow),
	initialized(false),
	hud(*this),
	saveZone(Game::getResolution().x / 2 - 200.0f,Game::getResolution().y / 2 - 200.0f, 400.0f, 400.0f),
	level(1)
{
	texBackground = Game::textureManager.acquire(thor::Resources::TextureKey::fromFile("res/background.png"));
	background.setTexture(*texBackground);
	init();
}

void Singleplayer::init() {
	if(!initialized) {
		level = 1;
		spawnAsteroids(level);
		entityManager.add(new Spaceship(sf::Vector2f(20.0f,20.0f)), SPACESHIP);
	}
}

void Singleplayer::reinit() {
	entityManager.clear();
	initialized = false;
	init();
}

unsigned short Singleplayer::update(float deltaTime) {

    sf::Event e;
    while (renderWindow.pollEvent(e)) {
        if (e.type == sf::Event::Closed)
            renderWindow.close();
		else if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape)
			return Game::MAIN_MENU;
		else if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::H)
			entityManager.showHitBox = !entityManager.showHitBox;
    }
	entityManager.update(deltaTime);
	hud.update(deltaTime);

	if(Asteroid::getAsteroidCount() <= 0) {
		++level;
		entityManager.getEntity(SPACESHIP)->reset();
		spawnAsteroids(level);
	}

	Spaceship* spaceship = dynamic_cast<Spaceship*>(Singleplayer::entityManager.getEntity(Singleplayer::SPACESHIP));
	if(spaceship) {
		if(spaceship->getLifes() <= 0) {
			return Game::GAME_OVER;
		}
	}

	return Game::SINGLEPLAYER;
}

void Singleplayer::draw() {
	renderWindow.draw(background);
	entityManager.draw(renderWindow);
	hud.draw(renderWindow);
}

void Singleplayer::spawnAsteroids(int lvl) {

	for(int i = 0; i < lvl; ++i) {

		// choose a random position
		sf::Vector2f pos;
		do {
			pos.x = thor::random(0.0f,float(Game::getResolution().x));
			pos.y = thor::random(0.0f,float(Game::getResolution().y));
		} while(saveZone.contains(pos)); // make sure the pos is not in the save zone

		// choose a random velocity
		float min = Game::config["asteroid.minSpeed"].as<float>();
		float max = Game::config["asteroid.maxSpeed"].as<float>();
		sf::Vector2f speed;
		if(thor::random(0,1) == 1) {
			speed.x = thor::random(min,max);
		} else {
			speed.x = thor::random(-max,-min);
		}
		if(thor::random(0,1) == 1) {
			speed.y = thor::random(min,max);
		} else {
			speed.y = thor::random(-max,-min);
		}

		entityManager.add(new Asteroid(pos,speed,Asteroid::BIG, thor::random(0.0f,360.0f)));
	}
}
