/**
* Copyright (c) 2012, Jens Mölzer
* This file is part of the asteroids project and is realeased under the BSD 2-Clause License.
* For more Details on licensing, see 'LICENCE.txt'.
**/

#pragma once

#include "Button.hpp"
#include "Gamestate.hpp"
#include "Game.hpp"
#include "Spaceship.hpp"
#include "MessageReceiver.hpp"
#include <SFML/Graphics.hpp>
#include <Thor/Resources.hpp>
#include <vector>
#include <string>

class MainMenu : public Gamestate, public MessageReceiver {

public:
	MainMenu(sf::RenderWindow& renderWindow);
    ~MainMenu();
	virtual void init();
	virtual void reinit();
	virtual unsigned short update(float deltaTime);
	virtual void draw();

    virtual void receiveMessage(unsigned int msg, const std::vector<boost::any>& params);

	void callbackNewGame();
	void callbackExit();
	void callbackResume();
    void callbackHighscore();

private:
	Button btnResume, btnNewGame, btnExit, btnHighscore;
	sf::RenderWindow& renderWindow;
	bool gameStarted;
	std::shared_ptr<sf::Texture> texBackground;
	sf::Sprite background;
	std::shared_ptr<sf::Font> font;
	sf::Text version;
	bool initialized;
	unsigned short newState;
    sf::Text txtTitle;

};
