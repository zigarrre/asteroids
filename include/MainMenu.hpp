#pragma once

#include "Gamestate.hpp"
#include "Game.hpp"
#include <SFML/Graphics.hpp>
#include <Thor/Resources.hpp>
#include <vector>
#include <string>

class MainMenu : public Gamestate {

public:
	MainMenu(sf::RenderWindow& renderWindow);
	virtual Gamestates update(float deltaTime);
	virtual void draw();

private:
	sf::RenderWindow& renderWindow;
	std::map<std::string,thor::ResourcePtr<sf::Texture>> textures;
	std::vector<sf::Sprite> buttons;

};