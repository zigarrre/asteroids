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

	texLife = Game::textureManager.Acquire(thor::Resources::TextureKey::FromFile("res/life.png"));
	font = Game::fontManager.Acquire(thor::Resources::FontKey::FromFile("res/font.ttf"));
	currentLevel.SetFont(*font);
	currentLevel.SetPosition(Game::getResolution().x - 150.0f, 10.0f);
	currentLevel.SetCharacterSize(15);
	currentLevel.SetColor(sf::Color::White);
}

void HUD::update(float deltaTime) {
	Spaceship* spaceship = dynamic_cast<Spaceship*>(Singleplayer::entityManager.getEntity(Singleplayer::SPACESHIP));
	if(spaceship) {
		// TODO needs better solution
		lifes.clear();
		if(spaceship->getLifes() > 1) {
			for(unsigned int i = 0; i < spaceship->getLifes() -1; ++i) {
				sf::Sprite* life = new sf::Sprite(*texLife);
				life->SetPosition(10.0f+life->GetGlobalBounds().Width*i+10,10.0f);
				lifes.push_back(life);
			}
		}
	}
	currentLevel.SetString("Level   " + rrr::toString(singleplayer.getLevel()));
}

void HUD::draw(sf::RenderTarget& renderTarget) {
	for(unsigned int i = 0; i < lifes.size(); ++i) {
		renderTarget.Draw(*lifes[i]);
	}
	renderTarget.Draw(currentLevel);
}
