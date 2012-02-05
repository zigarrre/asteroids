#include "Button.hpp"
#include "Game.hpp" // include here and not in header to avoid problems with headers (maybe include loop)

Button::Button(const sf::Vector2f& pos, const std::string& text, int (*onClickCallback)()) {

	// load textures
	bgNormal = Game::textureManager.Acquire(thor::Resources::TextureKey::FromFile("res/buttonNormal.png"));
	bgActive = Game::textureManager.Acquire(thor::Resources::TextureKey::FromFile("res/buttonActive.png"));

	// load font
	font = Game::fontManager.Acquire(thor::Resources::FontKey::FromFile("res/font.ttf"));

	background.SetTexture(*bgNormal);
	background.SetPosition(pos);

	this->text.SetFont(*font);
	this->text.SetString(text);
	this->text.SetPosition(pos.x+10,pos.y+10);

	onClick = onClickCallback;

}

void Button::draw(sf::RenderTarget& renderTarget) {
	renderTarget.Draw(background);
	renderTarget.Draw(text);
}

void Button::setActive(bool active) {
	if(active)
		background.SetTexture(*bgActive);
	else
		background.SetTexture(*bgNormal);
}

sf::Vector2f Button::getSize() {
	sf::Vector2f rv;
	rv.x = background.GetGlobalBounds().Width;
	rv.y = background.GetGlobalBounds().Height;
	return rv;
}