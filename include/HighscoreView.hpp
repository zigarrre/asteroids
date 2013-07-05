/**
* Copyright (c) 2012, Jens Mölzer
* This file is part of the asteroids project and is realeased under the BSD 2-Clause License.
* For more Details on licensing, see 'LICENCE.txt'.
**/

#pragma once

#include "ButtonManager.hpp"
#include "Gamestate.hpp"
#include "Game.hpp"
#include "Spaceship.hpp"
#include <SFML/Graphics.hpp>
#include <Thor/Resources.hpp>
#include <vector>

class HighscoreView : public Gamestate {

public:
    HighscoreView(sf::RenderWindow& renderWindow);
    virtual void init();
    virtual void reinit();
    virtual unsigned short update(float deltaTime);
    virtual void draw();

    void callbackRestart();
    void callbackMenu();

private:
    bool initialized;
    unsigned short newState;
    sf::RenderWindow& renderWindow;
    ButtonManager btnManager;
    std::shared_ptr<sf::Texture> texBackground;
    sf::Sprite background;
    std::shared_ptr<sf::Font> font;
    sf::Text txtTitle;

    // the 3 columns for the table
    sf::Text txtTableNumber;
    sf::Text txtTableName;
    std::vector<sf::Text> txtTableScore; // every line is a single sf::Text object because it's the only way to right align it

};
