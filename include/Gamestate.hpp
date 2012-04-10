/**
* Copyright (c) 2012, Jens Mölzer
* This file is part of the asteroids project and is realeased under the BSD 2-Clause License.
* For more Details on licensing, see 'LICENCE.txt'.
**/

#pragma once

#include <SFML/Graphics.hpp>

class Gamestate {
    public:
        Gamestate() {}
        virtual ~Gamestate() {}
		virtual void init() = 0;
		virtual void reinit() = 0;
        virtual unsigned short update(float deltaTime) = 0;
        virtual void draw() = 0;
    protected:
    private:
};
