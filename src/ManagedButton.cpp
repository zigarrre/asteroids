/**
* Copyright (c) 2012, Jens Mölzer
* This file is part of the asteroids project and is realeased under the BSD 2-Clause License.
* For more Details on licensing, see 'LICENCE.txt'.
**/

#include "ManagedButton.hpp"
#include "Game.hpp"
#include <Thor/Resources.hpp>

ManagedButton::ManagedButton(const sf::Vector2f& pos, const std::string& text, boost::function<void ()> onClickCallback) :
    enabled(true),
    active(false),
    onClick(onClickCallback)
{
    // load textures
    bgNormal = Game::getHandle().textureManager.acquire(thor::Resources::fromFile<sf::Texture>("res/buttonNormal.png"));
    bgActive = Game::getHandle().textureManager.acquire(thor::Resources::fromFile<sf::Texture>("res/buttonActive.png"));
    bgDisabled = Game::getHandle().textureManager.acquire(thor::Resources::fromFile<sf::Texture>("res/buttonDisabled.png"));

    // load font
    font = Game::getHandle().fontManager.acquire(thor::Resources::fromFile<sf::Font>("res/font.ttf"));

    background.setTexture(*bgNormal);
    background.setPosition(pos);

    this->text.setFont(*font);
    this->text.setString(text);
    this->text.setPosition(pos.x+background.getLocalBounds().width/2-this->text.getLocalBounds().width/2,pos.y+12);
    this->text.setColor(sf::Color(255,255,255));

}

void ManagedButton::setActive(bool active) {
    if(this->active != active && enabled) {
        this->active = active;
        if(active) {
            background.setTexture(*bgActive);
        } else {
            background.setTexture(*bgNormal);
        }
    }
}

void ManagedButton::setEnabled(bool enabled) {
    if(this->enabled != enabled) { // new state different than the old?
        this->enabled = enabled;
        if(enabled) {
            background.setTexture(*bgNormal);
            text.setColor(sf::Color(255,255,255));
        } else {
            background.setTexture(*bgDisabled);
            text.setColor(sf::Color(180,180,180));
        }
    }
}

void ManagedButton::draw(sf::RenderTarget& renderTarget) {
    renderTarget.draw(background);
    renderTarget.draw(text);
}

bool ManagedButton::isOver(sf::Vector2i cord) {
    if((cord.x > background.getPosition().x && cord.x < (background.getPosition().x+background.getGlobalBounds().width)) && (cord.y > background.getPosition().y && cord.y < (background.getPosition().y+background.getGlobalBounds().height)))
        return true;
    else
        return false;
}

sf::Vector2f ManagedButton::getSize() {
    sf::Vector2f rv;
    rv.x = background.getGlobalBounds().width;
    rv.y = background.getGlobalBounds().height;
    return rv;
}
