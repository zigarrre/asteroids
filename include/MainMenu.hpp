#pragma once

#include "Button.hpp"
#include "Gamestate.hpp"
#include "Game.hpp"
#include "Spaceship.hpp"
#include <SFML/Graphics.hpp>
#include <Thor/Resources.hpp>
#include <vector>
#include <string>

class MainMenu : public Gamestate {

public:
	MainMenu(sf::RenderWindow& renderWindow);
	virtual void init();
	virtual void reinit();
	virtual unsigned short update(float deltaTime);
	virtual void draw();

	int callbackNewGame();
	int callbackExit();
	int callbackResume();

private:
	Button btnResume, btnNewGame, btnExit;
	sf::RenderWindow& renderWindow;
	bool gameStarted;
	thor::ResourcePtr<sf::Texture> texBackground;
	sf::Sprite background;
	thor::ResourcePtr<sf::Font> font;
	sf::Text version;
	bool initialized;

	unsigned short handleMouseClick(const sf::Vector2i& mouseCord);

};
