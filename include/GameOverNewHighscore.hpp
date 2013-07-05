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
    bool initialized;
    unsigned short newState;
    sf::RenderWindow& renderWindow;
    ButtonManager btnManager;
    std::shared_ptr<sf::Texture> texBackground;
    sf::Sprite background;
    std::shared_ptr<sf::Font> font;
    std::string name;
    sf::Text txtTitle;
    sf::Text txtNewHighscore;
    sf::Text txtName;
    unsigned short maxNameLength;

};
