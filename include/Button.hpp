#pragma once

#include "Game.hpp"
#include <Thor/Resources.hpp>
#include <SFML/Graphics.hpp>
#include <string>

class Button {

public:

	Button(const sf::Vector2f& pos, const std::string& text, int (*onClickCallback)());

	/// Draws all part of the button to the given sf::RenderTarget
	void draw(sf::RenderTarget& renderTarget);

	/// if button is set to aktive it will change appearance (mouseover effect)
	void setActive(bool active);

	int (*onClick)();

private:
	thor::ResourcePtr<sf::Texture> bgNormal;
	thor::ResourcePtr<sf::Texture> bgActive;
	thor::ResourcePtr<sf::Font> font;
	sf::Sprite background;
	sf::Text text;
};