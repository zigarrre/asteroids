/**
* Copyright (c) 2012, Jens Mölzer
* This file is part of the asteroids project and is realeased under the BSD 2-Clause License.
* For more Details on licensing, see 'LICENCE.txt'.
**/

#include "ButtonManager.hpp"
//#include <SFML/System.hpp>
#include <iostream>

using namespace std;

ButtonManager::ButtonManager(const sf::Vector2f& pos, sf::RenderWindow& renderWindow) :
    renderWindow(renderWindow),
    activeButton(0),
    layout(VERTICALLY),
    space(20),
    pos(pos),
    mouseWasPressed(false),
    buttonDelay(0.15f),
    cooldownBtnUp(0.0f),
    cooldownBtnDown(0.0f)
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
        
        } else {
            buttons[i]->setActive(false);
        }
    }
    
    
    if(layout == VERTICALLY) {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && cooldownBtnDown <= 0.0f && activeButton < buttons.size()-1) {
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
        } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && cooldownBtnUp <= 0.0f && activeButton > 0) {
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
        }
    }
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && activeButton >= 0 && activeButton < buttons.size()) {
        buttons[activeButton]->click();
    }
    
    if(cooldownBtnUp > 0.0f)
        cooldownBtnUp -= deltaTime;
    if(cooldownBtnDown > 0.0f)
        cooldownBtnDown -= deltaTime;
    
    mouseWasPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
}

void ButtonManager::draw() {
    for(auto button : buttons)
        button->draw(renderWindow);
}

std::shared_ptr<ManagedButton> ButtonManager::createButton(const std::string& text, boost::function<void ()> onClickCallback) {
    sf::Vector2f position = {0,0};
    if(buttons.size() == 0) {
        position = pos;
    } else if(layout == VERTICALLY){
        position = {pos.x, buttons[buttons.size()-1]->getPosition().y + buttons[buttons.size()-1]->getSize().y + space};
    } else if(layout == HORIZONTALLY) {
        position = {buttons[buttons.size()-1]->getPosition().x + buttons[buttons.size()-1]->getSize().x + space, pos.y};
    }
    return std::shared_ptr<ManagedButton>(new ManagedButton(position, text, onClickCallback));
}

void ButtonManager::addButton(const std::string& text, boost::function<void ()> onClickCallback) {
    buttons.push_back(createButton(text, onClickCallback));
}

void ButtonManager::addButton(std::shared_ptr<ManagedButton> button) {
    buttons.push_back(button);
}

void ButtonManager::removeButton(size_t index) {
    
}

void ButtonManager::setLayout(unsigned int layout) {
    this->layout = layout;
}
