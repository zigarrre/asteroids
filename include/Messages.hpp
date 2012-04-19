/**
* Copyright (c) 2012, Jens Mölzer
* This file is part of the asteroids project and is realeased under the BSD 2-Clause License.
* For more Details on licensing, see 'LICENCE.txt'.
**/

#pragma once

/**
* Define different types of messages for the inter-entity-messagesystem
*
* If a message has parameters, these are listet under the description in exact the order in which the should be in the vector.
**/
struct Messages {
    enum {

        /**
        * Deals a given amount of damage to the entity
        * Parameters:
        *   int: The ammount of damage to deal
        **/
        TAKE_DAMAGE = 0
    };
};

/**
* Define different types of messages for the engine-messagesystem
*
* If a message has parameters, these are listet under the description in exact the order in which the should be in the vector.
**/
struct EngineMessages {
    enum {

        /**
        * The player has died.
        * no parameters
        **/
        PLAYER_DIED = 0,

        /**
        * A asteroid was destroyed.
        * no parameters
        **/
        ASTEROID_DESTROYED

    };
};