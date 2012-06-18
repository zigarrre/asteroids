/**
* Copyright (c) 2012, Jens Mölzer
* This file is part of the asteroids project and is realeased under the BSD 2-Clause License.
* For more Details on licensing, see 'LICENCE.txt'.
**/

#include "Button.hpp"
#include "Game.hpp" // include here and not in header to avoid problems with headers (maybe include loop)

#include <iostream>
using namespace std;

Button::Button(const sf::Vector2f& pos, const std::string& text, boost::function<void ()> onClickCallback, sf::RenderWindow &renderWindow) :
    renderWindow(renderWindow),
    enabled(true),
    mouseWasPressed(false)
{

    // load textures
    bgNormal = Game::getHandle().textureManager.acquire(thor::Resources::TextureKey::fromFile("res/buttonNormal.png"));
    bgActive = Game::getHandle().textureManager.acquire(thor::Resources::TextureKey::fromFile("res/buttonActive.png"));
    bgDisabled = Game::getHandle().textureManager.acquire(thor::Resources::TextureKey::fromFile("res/buttonDisabled.png"));

    // load font
    font = Game::getHandle().fontManager.acquire(thor::Resources::FontKey::fromFile("res/font.ttf"));

    background.setTexture(*bgNormal);
    background.setPosition(pos);

    this->text.setFont(*font);
    this->text.setString(text);
    this->text.setPosition(pos.x+background.getLocalBounds().width/2-this->text.getLocalBounds().width/2,pos.y+12);
    this->text.setColor(sf::Color(255,255,255));

    onClick = onClickCallback;

}

void Button::update(float deltaTime) {

    if(enabled) {

        // clicked?
        // only react on button release (check if button was pressed last frame but not this frame)
        if(mouseWasPressed && !sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->isOver(sf::Mouse::getPosition(renderWindow)))
            onClick();
        mouseWasPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);

        // mouse over
        if(isOver(sf::Mouse::getPosition(renderWindow))) {
            background.setTexture(*bgActive);
        } else {
            background.setTexture(*bgNormal);
        }

    }

}

void Button::draw() {
    renderWindow.draw(background);
    renderWindow.draw(text);
}

bool Button::isOver(sf::Vector2i cord) {
    if((cord.x > background.getPosition().x && cord.x < (background.getPosition().x+background.getGlobalBounds().width)) && (cord.y > background.getPosition().y && cord.y < (background.getPosition().y+background.getGlobalBounds().height)))
        return true;
    else
        return false;
}

void Button::setEnabled(bool enabled) {
    this->enabled = enabled;
    if(!enabled) {
        background.setTexture(*bgDisabled);
        text.setColor(sf::Color(180,180,180));
    } else {
        background.setTexture(*bgNormal);
        text.setColor(sf::Color(255,255,255));
    }
}

sf::Vector2f Button::getSize() {
    sf::Vector2f rv;
    rv.x = background.getGlobalBounds().width;
    rv.y = background.getGlobalBounds().height;
    return rv;
}
