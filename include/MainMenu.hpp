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

// TODO move callbacks into class MainMenu to avoid ugly code in handleMouseClick()
int callbackNewGame();
int callbackExit();
int callbackResume();