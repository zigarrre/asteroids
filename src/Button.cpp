#include "Button.hpp"
#include "Game.hpp" // include here and not in header to avoid problems with headers (maybe include loop)

#include <iostream>
using namespace std;

Button::Button(const sf::Vector2f& pos, const std::string& text, boost::function<int ()> onClickCallback, sf::RenderWindow &renderWindow) :
	renderWindow(renderWindow),
	enabled(true)
{

	// load textures
	bgNormal = Game::textureManager.Acquire(thor::Resources::TextureKey::FromFile("res/buttonNormal.png"));
	bgActive = Game::textureManager.Acquire(thor::Resources::TextureKey::FromFile("res/buttonActive.png"));
	bgDisabled = Game::textureManager.Acquire(thor::Resources::TextureKey::FromFile("res/buttonDisabled.png"));

	// load font
	font = Game::fontManager.Acquire(thor::Resources::FontKey::FromFile("res/font.ttf"));

	background.SetTexture(*bgNormal);
	background.SetPosition(pos);

	this->text.SetFont(*font);
	this->text.SetString(text);
	this->text.SetPosition(pos.x+background.GetLocalBounds().Width/2-this->text.GetLocalBounds().Width/2,pos.y+12);
	this->text.SetColor(sf::Color(255,255,255));

	onClick = onClickCallback;

}

void Button::update(float deltaTime) {

	if(enabled) {
		// mouse over
		if(isOver(sf::Mouse::GetPosition(renderWindow))) {
			background.SetTexture(*bgActive);
		} else {
			background.SetTexture(*bgNormal);
		}
	}

}

void Button::draw() {
	renderWindow.Draw(background);
	renderWindow.Draw(text);
}

bool Button::isOver(sf::Vector2i cord) {
	if((cord.x > background.GetPosition().x && cord.x < (background.GetPosition().x+background.GetGlobalBounds().Width)) && (cord.y > background.GetPosition().y && cord.y < (background.GetPosition().y+background.GetGlobalBounds().Height)))
		return true;
	else
		return false;
}

void Button::setEnabled(bool enabled) {
	this->enabled = enabled;
	if(!enabled) {
		background.SetTexture(*bgDisabled);
		text.SetColor(sf::Color(180,180,180));
	} else {
		background.SetTexture(*bgNormal);
		text.SetColor(sf::Color(255,255,255));
	}
}

sf::Vector2f Button::getSize() {
	sf::Vector2f rv;
	rv.x = background.GetGlobalBounds().Width;
	rv.y = background.GetGlobalBounds().Height;
	return rv;
}
