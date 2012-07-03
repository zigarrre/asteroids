/**
* Copyright (c) 2012, Jens Mölzer
* This file is part of the asteroids project and is realeased under the BSD 2-Clause License.
* For more Details on licensing, see 'LICENCE.txt'.
**/

#pragma once

#include <SFML/Graphics.hpp>
#include <Thor/Resources.hpp>
#include <vector>

class Singleplayer;

class HUD {

public:

	HUD(const Singleplayer& singleplayer);

	void update(float deltaTime);

	void draw(sf::RenderTarget& renderTarget);

private:

	std::shared_ptr<sf::Texture> texLife;
	std::shared_ptr<sf::Font> font;
	std::vector<sf::Sprite*> lifes;
	sf::Text currentLevel;
    sf::Text score;
	const Singleplayer& singleplayer;

};