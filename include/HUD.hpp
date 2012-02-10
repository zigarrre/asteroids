#pragma once

#include <SFML/Graphics.hpp>
#include <Thor/Resources.hpp>
#include <vector>

class HUD {

public:

	HUD();

	void update(float deltaTime);

	void draw(sf::RenderTarget& renderTarget);

private:

	std::vector<sf::Sprite*> lifes;

	thor::ResourcePtr<sf::Texture> texLife;

};