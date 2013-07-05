/**
* Copyright (c) 2012, Jens Mölzer
* This file is part of the asteroids project and is realeased under the BSD 2-Clause License.
* For more Details on licensing, see 'LICENCE.txt'.
**/

#pragma once

#include "ManagedButton.hpp"
#include <vector>
#include <boost/function.hpp>

class ButtonManager {

public:

    ButtonManager(const sf::Vector2f& pos, sf::RenderWindow& renderWindow);
    
    /**
    * Update the ButtonManager, should be called every frame
    **/
    void update(float deltaTime);
    
    /**
    * Draw all buttons to the RenderWindow which was given in the constructor
    **/
    void draw();
    
    /**
    * Add a new button to the manager.
    *
    * Use this function if you don't need control over the button.
    **/
    void addButton(const std::string& text, boost::function<void ()> onClickCallback);
    
    /**
    * Add an existing button to the manager.
    *
    * Use this function of you need future control over the button
    *
    * Note: It is not recommended to call setPosition() or setActive() onto the button,
    * all other functions are okay.
    **/
    void addButton(std::shared_ptr<ManagedButton> button);
    
    /**
    * Remove a button from the manager
    **/
    void removeButton(size_t index);
    
    /**
    * Change the layout of the manager, possible layouts are specified as constants in this class
    **/
    void setLayout(unsigned int layout);
    
    enum { VERTICALLY = 0, HORIZONTALLY };
    
private:

    /**
    * Calculate the position of the button on the specified position.
    * Respects the current layout.
    **/
    sf::Vector2f calculateButtonPos(size_t index);

    std::vector<std::shared_ptr<ManagedButton>> buttons;
    sf::RenderWindow& renderWindow;
    size_t activeButton;
    unsigned int layout;
    int space;
    sf::Vector2f pos;
    bool mouseWasPressed; // state of the left mouse button in the last frame
    bool returnWasPressed;
    float buttonDelay; // aka button repeat delay
    float cooldownBtnUp, cooldownBtnDown;
    
};
