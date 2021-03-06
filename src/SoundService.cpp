#include "SoundService.hpp"

#include "Game.hpp"
#include "Messages.hpp"
#include "MessageSystem.hpp"

#include <Thor/Resources.hpp>

SoundService::SoundService() {
}

void SoundService::init() {
    // load sound buffers
    explosionSoundBuffer = Game::getHandle().soundManager.acquire(thor::Resources::fromFile<sf::SoundBuffer>(Game::getHandle().config["paths.res"].as<std::string>() + "/explosion.ogg"));

    // configure sounds
    explosionSound.setBuffer(*explosionSoundBuffer);

    // register with message system
    MessageSystem::getHandle().registerReceiver(this);
}

void SoundService::receiveMessage(unsigned int msg, const std::vector<boost::any>& params) {
    switch (msg)
    {
    case EngineMessages::ASTEROID_DESTROYED:
    case EngineMessages::PLAYER_DIED:
        explosionSound.play();
        break;
    }
}
