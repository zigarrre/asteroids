#include "HUD.hpp"
#include "Singleplayer.hpp"
#include "Game.hpp"
#include "Spaceship.hpp"

HUD::HUD()
{

	texLife = Game::textureManager.Acquire(thor::Resources::TextureKey::FromFile("res/life.png"));

}

void HUD::update(float deltaTime) {
	Spaceship* spaceship = dynamic_cast<Spaceship*>(Singleplayer::entityManager.getEntity(Singleplayer::SPACESHIP));
	if(spaceship) {
		// TODO needs better solution
		lifes.clear();
		for(unsigned int i = 0; i < spaceship->getLifes(); ++i) {
			sf::Sprite* life = new sf::Sprite(*texLife);
			life->SetPosition(10.0f+life->GetGlobalBounds().Width*i+10,10.0f);
			lifes.push_back(life);
		}
	}
}

void HUD::draw(sf::RenderTarget& renderTarget) {
	for(unsigned int i = 0; i < lifes.size(); ++i) {
		renderTarget.Draw(*lifes[i]);
	}
}
