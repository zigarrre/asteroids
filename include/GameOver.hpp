/**
* Copyright (c) 2012, Jens Mölzer
* This file is part of the asteroids project and is realeased under the BSD 2-Clause License.
* For more Details on licensing, see 'LICENCE.txt'.
**/

#pragma once

#include "ButtonManager.hpp"
#include "Gamestate.hpp"
#include "Game.hpp"
#include "Spaceship.hpp"
#include <SFML/Graphics.hpp>
#include <Thor/Resources.hpp>
#include <vector>
#include <string>

class GameOver : public Gamestate {

public:
	GameOver(sf::RenderWindow& renderWindow);
	virtual void init();
	virtual void reinit();
	virtual unsigned short update(float deltaTime);
	virtual void draw();

	void callbackRestart();
	void callbackMenu();

private:
    bool initialized;
	unsigned short newState;
	sf::RenderWindow& renderWindow;
	ButtonManager btnManager;
	std::shared_ptr<sf::Texture> texBackground;
    std::shared_ptr<sf::Font> font;
	sf::Sprite background;
    sf::Text txtTitle;

};
