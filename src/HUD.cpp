/**
* Copyright (c) 2012, Jens Mölzer
* This file is part of the asteroids project and is realeased under the BSD 2-Clause License.
* For more Details on licensing, see 'LICENCE.txt'.
**/

#include "HUD.hpp"
#include "Singleplayer.hpp"
#include "Game.hpp"
#include "Spaceship.hpp"
#include "utility.hpp"

HUD::HUD(const Singleplayer& singleplayer) :
	singleplayer(singleplayer)
{

	texLife = Game::textureManager.acquire(thor::Resources::TextureKey::fromFile("res/life.png"));
	font = Game::fontManager.acquire(thor::Resources::FontKey::fromFile("res/font.ttf"));
	currentLevel.setFont(*font);
	currentLevel.setPosition(Game::getResolution().x - 150.0f, 10.0f);
	currentLevel.setCharacterSize(15);
	currentLevel.setColor(sf::Color::White);
}

void HUD::update(float deltaTime) {
	Spaceship* spaceship = dynamic_cast<Spaceship*>(Singleplayer::entityManager.getEntity(Singleplayer::SPACESHIP));
	if(spaceship) {
		// TODO needs better solution
		lifes.clear();
		if(spaceship->getLifes() > 1) {
			for(unsigned int i = 0; i < spaceship->getLifes() -1; ++i) {
				sf::Sprite* life = new sf::Sprite(*texLife);
				life->setPosition(10.0f+life->getGlobalBounds().width*i+10,10.0f);
				lifes.push_back(life);
			}
		}
	}
	currentLevel.setString("Level   " + rrr::toString(singleplayer.getLevel()));
}

void HUD::draw(sf::RenderTarget& renderTarget) {
	for(unsigned int i = 0; i < lifes.size(); ++i) {
		renderTarget.draw(*lifes[i]);
	}
	renderTarget.draw(currentLevel);
}
