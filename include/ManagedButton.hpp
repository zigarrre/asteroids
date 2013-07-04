/**
* Copyright (c) 2012, Jens Mölzer
* This file is part of the asteroids project and is realeased under the BSD 2-Clause License.
* For more Details on licensing, see 'LICENCE.txt'.
**/

#pragma once

#include <SFML/Graphics.hpp>
#include <boost/function.hpp>

class ManagedButton {

public:
    ManagedButton(const sf::Vector2f& pos, const std::string& text, boost::function<void ()> onClickCallback);
    void setActive(bool active);
    bool getActive() const { return active; }
    void setEnabled(bool enabled);
    bool getEnabled() const { return enabled; }
    void draw(sf::RenderTarget& renderTarget);
    bool isOver(sf::Vector2i cord);
    void click() { if(enabled) onClick(); }
    sf::Vector2f getPosition() { return background.getPosition(); }
    sf::Vector2f getSize();

private:
    std::shared_ptr<sf::Texture> bgNormal;
    std::shared_ptr<sf::Texture> bgActive;
    std::shared_ptr<sf::Texture> bgDisabled;
    std::shared_ptr<sf::Font> font;
    sf::Sprite background;
    sf::Text text;
    bool enabled;
    bool active;
    boost::function<void ()> onClick;
    
};
