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
    
    ManagedButton(const std::string& text, boost::function<void ()> onClickCallback);
    
    /**
    * Set the visual state of the button to active or notactive (mouse-over effect)
    **/
    void setActive(bool active);
    
    /**
    * Determine if the button is active
    **/
    bool getActive() const { return active; }
    
    /**
    * Enables/Disables the button.
    * 
    * When disabled the button is displayed grayed out (overrides active visual) and click() does nothing
    **/
    void setEnabled(bool enabled);
    
    /**
    * Determine if the button is enabled
    **/
    bool getEnabled() const { return enabled; }
    
    /**
    * Draws the button to the given sf::RenderTarget
    **/
    void draw(sf::RenderTarget& renderTarget);
    
    /**
    * Determine if the mouse is currently over this button
    **/
    bool isOver(sf::Vector2i cord);
    
    /**
    * Execute the onClickCallback function
    **/
    void click() { if(enabled) onClick(); }
    
    /**
    * Set the postion of the button
    **/
    void setPosition(const sf::Vector2f& pos);
    
    /**
    * Return the postion of the button
    **/
    sf::Vector2f getPosition() { return background.getPosition(); }
    
    /**
    * Return the size of the button
    **/
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
