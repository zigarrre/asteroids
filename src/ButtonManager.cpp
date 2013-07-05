/**
* Copyright (c) 2013, Jens Mölzer
* This file is part of the asteroids project and is realeased under the BSD 2-Clause License.
* For more Details on licensing, see 'LICENCE.txt'.
**/

#include "ButtonManager.hpp"

using namespace std;

ButtonManager::ButtonManager(const sf::Vector2f& pos, sf::RenderWindow& renderWindow) :
    renderWindow(renderWindow),
    activeButton(0),
    layout(VERTICALLY),
    space(20),
    pos(pos),
    mouseWasPressed(false),
    returnWasPressed(true), // asume true (in the first frame) to prevent accidentialy skipping through menus
    buttonDelay(0.2f),
    cooldownBtnUp(0.4f), // non zero to prevent input through still held down keys from the last menu
    cooldownBtnDown(0.4f)
{
}

void ButtonManager::update(float deltaTime) {
    for(size_t i = 0; i < buttons.size(); ++i) {
        if(buttons[i]->isOver(sf::Mouse::getPosition(renderWindow)) && buttons[i]->getEnabled()) {
            buttons[i]->setActive(true);
            activeButton = i;
            if(mouseWasPressed && !sf::Mouse::isButtonPressed(sf::Mouse::Left))
                buttons[i]->click();
        } else if(i == activeButton) {
            // ensure that the button is displayed as active
            if(!buttons[i]->getActive())
                buttons[i]->setActive(true);
        } else {
            buttons[i]->setActive(false);
        }
    }
    
    
    if( (
            (layout == VERTICALLY && sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) ||
            (layout == HORIZONTALLY && sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        ) &&
        cooldownBtnDown <= 0.0f && activeButton < buttons.size()-1)
    {
        // find the next enabled button
        unsigned int i = activeButton+1;
        bool validButtonFound = false;
        while((i < buttons.size()) && !validButtonFound) {
            if(buttons[i]->getEnabled())
                validButtonFound = true;
            else
                ++i;
        }
        
        if(validButtonFound) {
            buttons[activeButton]->setActive(false);
            activeButton = i;
            buttons[activeButton]->setActive(true);
        }
        
        cooldownBtnDown = buttonDelay;
    } else if( (
                    (layout == VERTICALLY && sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) ||
                    (layout == HORIZONTALLY && sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
               ) &&
               cooldownBtnUp <= 0.0f && activeButton > 0)
    {
               
        // find the next enabled button
        int i = activeButton-1;
        bool validButtonFound = false;
        while((i >= 0) && !validButtonFound) {
            if(buttons[i]->getEnabled())
                validButtonFound = true;
            else
                --i;
        }
        
        if(validButtonFound) {
            buttons[activeButton]->setActive(false);
            activeButton = i;
            buttons[activeButton]->setActive(true);
        }
        
        cooldownBtnUp = buttonDelay;
    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return) &&
        !returnWasPressed &&
        activeButton >= 0 &&
        activeButton < buttons.size())
    {
        buttons[activeButton]->click();
    }
    
    if(cooldownBtnUp > 0.0f)
        cooldownBtnUp -= deltaTime;
    if(cooldownBtnDown > 0.0f)
        cooldownBtnDown -= deltaTime;
    
    mouseWasPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
    returnWasPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Return);
}

void ButtonManager::draw() {
    for(auto button : buttons)
        button->draw(renderWindow);
}

void ButtonManager::addButton(const std::string& text, boost::function<void ()> onClickCallback) {
    buttons.push_back(std::shared_ptr<ManagedButton>(new ManagedButton(calculateButtonPos(buttons.size()), text, onClickCallback)));
}

void ButtonManager::addButton(std::shared_ptr<ManagedButton> button) {
    button->setPosition(calculateButtonPos(buttons.size()));
    buttons.push_back(button);
}

void ButtonManager::removeButton(size_t index) {
    if(index < buttons.size()) {
        buttons.erase(buttons.begin() + index);
        for(size_t i = index; i < buttons.size(); ++i)
            buttons[i]->setPosition(calculateButtonPos(index));
    }
}

void ButtonManager::setLayout(unsigned int layout) {
    this->layout = layout;
}

sf::Vector2f ButtonManager::calculateButtonPos(size_t index) {
    if(index == 0)
        return pos;

    shared_ptr<ManagedButton> btn;
    if(buttons.size() > 0) {
        btn = buttons[0];
    } else {
        btn = make_shared<ManagedButton>(pos, "", boost::function<void ()>(0));
    }
    
    if(layout == VERTICALLY){
        return sf::Vector2f(pos.x, pos.y + (btn->getSize().y + space) * index);
    } else if(layout == HORIZONTALLY) {
        return sf::Vector2f(pos.x + (btn->getSize().x + space) * index, pos.y);
    } else {
        return pos; // not supported layout
    }
}
