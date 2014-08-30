#pragma once

#include "MessageReceiver.hpp"

#include <memory>
#include <SFML/Audio.hpp>

/**
* \brief Used to play sounds triggered by Messages from the MessageSystem
*/
class SoundService : public MessageReceiver {

public:

    SoundService();

    virtual void receiveMessage(unsigned int msg, const std::vector<boost::any>& params);

private:

    std::shared_ptr<sf::SoundBuffer> explosionSoundBuffer;
    sf::Sound explosionSound;

};