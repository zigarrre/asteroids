/**
* Copyright (c) 2012, Jens Mölzer
* This file is part of the asteroids project and is realeased under the BSD 2-Clause License.
* For more Details on licensing, see 'LICENCE.txt'.
**/

#pragma once

#include <Thor/Resources.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <boost/function.hpp>
#include <boost/bind.hpp>

class Button {

public:

	Button(const sf::Vector2f& pos, const std::string& text, boost::function<int ()> onClickCallback, sf::RenderWindow &renderWindow);

	void update(float deltaTime);

	/// Draws all part of the button to the given sf::RenderTarget
	void draw();

	/// returns true if the given coordinates are over the button
	bool isOver(sf::Vector2i cord);

	/// button turn grey and doesn't react to user input anymore
	void setEnabled(bool enabled);

	sf::Vector2f getPosition() { return background.GetPosition(); }

	sf::Vector2f getSize();

	boost::function<int ()> onClick;

private:
	thor::ResourcePtr<sf::Texture> bgNormal;
	thor::ResourcePtr<sf::Texture> bgActive;
	thor::ResourcePtr<sf::Texture> bgDisabled;
	thor::ResourcePtr<sf::Font> font;
	sf::Sprite background;
	sf::Text text;
	bool enabled;
	sf::RenderWindow &renderWindow;

};