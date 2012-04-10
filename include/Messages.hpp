/**
* Copyright (c) 2012, Jens Mölzer
* This file is part of the asteroids project and is realeased under the BSD 2-Clause License.
* For more Details on licensing, see 'LICENCE.txt'.
**/

#pragma once

/**
* Define the different Types of Messages
**/
struct Messages {

    enum {

        /*************
        * Deals a given amount of damage to the entity
        * Parameters:
        *   int: The ammount of damage to deal
        *************/
        TAKE_DAMAGE = 0,
    };

};