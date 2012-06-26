/**
* Copyright (c) 2012, Jens Mölzer
* This file is part of the asteroids project and is realeased under the BSD 2-Clause License.
* For more Details on licensing, see 'LICENCE.txt'.
**/

#pragma once

#include "Button.hpp"
#include "Gamestate.hpp"
#include "Game.hpp"
#include "Spaceship.hpp"
#include <SFML/Graphics.hpp>
#include <Thor/Resources.hpp>
#include <vector>
#include <string>

class GameOverNewHighscore : public Gamestate {

public:
    GameOverNewHighscore(sf::RenderWindow& renderWindow);
    virtual void init();
    virtual void reinit();
    virtual unsigned short update(float deltaTime);
    virtual void draw();

    void callbackOK();

private:
    Button btnOK;
    sf::RenderWindow& renderWindow;
    thor::ResourcePtr<sf::Texture> texBackground;
    sf::Sprite background;
    bool initialized;
    unsigned short newState;
    thor::ResourcePtr<sf::Font> font;
    std::string name;
    sf::Text txtTitle;
    sf::Text txtNewHighscore;
    sf::Text txtName;
    unsigned short maxNameLength;

};
