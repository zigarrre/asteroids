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

	texLife = Game::getHandle().textureManager.acquire(thor::Resources::fromFile<sf::Texture>("res/life.png"));
	font = Game::getHandle().fontManager.acquire(thor::Resources::fromFile<sf::Font>("res/font.ttf"));
	currentLevel.setFont(*font);
	currentLevel.setPosition(Game::getHandle().getResolution().x - 10.0f, 10.0f);
	currentLevel.setCharacterSize(15);
	currentLevel.setColor(sf::Color::White);
    score.setFont(*font);
	score.setPosition(Game::getHandle().getResolution().x - 10.0f, 30.0f);
	score.setCharacterSize(15);
	score.setColor(sf::Color::White);
}

void HUD::update(float deltaTime) {

	if(singleplayer.getLifes() > 0) {
		if(lifes.size() < (singleplayer.getLifes() - 1)) {
			for(unsigned int i = lifes.size(); i < singleplayer.getLifes() - 1; ++i) {
				sf::Sprite* life = new sf::Sprite(*texLife);
				life->setPosition(10.0f+life->getGlobalBounds().width*i+10,10.0f);
				lifes.push_back(life);
			}
		} else {
			while(lifes.size() > (singleplayer.getLifes() - 1))
				lifes.pop_back();
		}
	}

	currentLevel.setString("Level   " + rrr::toString(singleplayer.getLevel()));
    currentLevel.setOrigin(currentLevel.getLocalBounds().width, 0); // set origin to the right upper corner to right-align the text
    score.setString(rrr::toString(Game::getHandle().highscore.getCurrentScore()));
    score.setOrigin(score.getLocalBounds().width, 0);
}

void HUD::draw(sf::RenderTarget& renderTarget) {
	for(unsigned int i = 0; i < lifes.size(); ++i) {
		renderTarget.draw(*lifes[i]);
	}
	renderTarget.draw(currentLevel);
    renderTarget.draw(score);
}
