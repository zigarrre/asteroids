#include "Singleplayer.hpp"

Singleplayer::Singleplayer(sf::RenderWindow& renderWindow) :
    renderWindow(renderWindow)
{
    entitys.push_back(new Spaceship(sf::Vector2f(20.0f,20.0f)));
}

Singleplayer::~Singleplayer() {
    for(unsigned int i = 0; i < entitys.size();++i) {
        delete entitys[i];
        entitys.erase(entitys.begin()+i);
    }
}

int Singleplayer::update(float deltaTime) {

    sf::Event Event;
    while (renderWindow.PollEvent(Event)) {
        if (Event.Type == sf::Event::Closed)
            renderWindow.Close();
    }
    for(unsigned int i = 0; i < entitys.size();++i) {
        entitys[i]->update(deltaTime);
		//std::cout<<"update"<<std::endl;
    }

    return GAMESTATE_SINGLEPLAYER;
}

void Singleplayer::draw() {
    for(unsigned int i = 0; i < entitys.size();++i) {
        renderWindow.Draw(*entitys[i]);
		//std::cout<<"draw"<<std::endl;
    }
}
