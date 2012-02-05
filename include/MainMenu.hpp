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
	virtual unsigned short update(float deltaTime);
	virtual void draw();

private:
	std::vector<Button> buttons;
	sf::RenderWindow& renderWindow;
	bool gameStarted;
	thor::ResourcePtr<sf::Texture> texBackground;
	sf::Sprite background;

	unsigned short handleMouseClick(int mouseX, int mouseY);

};

int callbackNewGame();
int callbackExit();