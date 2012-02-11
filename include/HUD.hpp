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

	thor::ResourcePtr<sf::Texture> texLife;
	thor::ResourcePtr<sf::Font> font;
	std::vector<sf::Sprite*> lifes;
	sf::Text currentLevel;
	const Singleplayer& singleplayer;

};