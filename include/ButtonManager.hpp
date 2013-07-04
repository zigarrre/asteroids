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
    void update(float deltaTime);
    void draw();
    void addButton(const std::string& text, boost::function<void ()> onClickCallback);
    void addButton(std::shared_ptr<ManagedButton> button);
    void removeButton(size_t index);
    void setLayout(unsigned int layout);
    
    enum { VERTICALLY = 0, HORIZONTALLY };
    
private:

    sf::Vector2f calculateButtonPos(size_t index, unsigned int layout);

    std::vector<std::shared_ptr<ManagedButton>> buttons;
    sf::RenderWindow& renderWindow;
    size_t activeButton;
    unsigned int layout;
    int space;
    sf::Vector2f pos;
    bool mouseWasPressed; // state of the left mouse button in the last frame
    float buttonDelay;
    float cooldownBtnUp, cooldownBtnDown;
    
};
