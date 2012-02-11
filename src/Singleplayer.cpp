#include "Singleplayer.hpp"

EntityManager Singleplayer::entityManager(10);

Singleplayer::Singleplayer(sf::RenderWindow& renderWindow) :
    renderWindow(renderWindow),
	initialized(false),
	hud(*this),
	saveZone(Game::getResolution().x/2-200.0f,Game::getResolution().y-200.0f,200.0f,200.0f),
	level(1)
{
	texBackground = Game::textureManager.Acquire(thor::Resources::TextureKey::FromFile("res/background.png"));
	background.SetTexture(*texBackground);
	init();
}

void Singleplayer::init() {
	if(!initialized) {
		spawnAsteroids(level);
		entityManager.add(new Spaceship(sf::Vector2f(20.0f,20.0f)), SPACESHIP);
	}
}

void Singleplayer::reinit() {
	entityManager.clear();
	initialized = false;
	init();
}

unsigned short Singleplayer::update(float deltaTime) {

    sf::Event e;
    while (renderWindow.PollEvent(e)) {
        if (e.Type == sf::Event::Closed)
            renderWindow.Close();
		else if (e.Type == sf::Event::KeyPressed && e.Key.Code == sf::Keyboard::Escape)
			return Game::MAIN_MENU;
		else if (e.Type == sf::Event::KeyPressed && e.Key.Code == sf::Keyboard::H)
			entityManager.showHitBox = !entityManager.showHitBox;
    }
	entityManager.update(deltaTime);
	hud.update(deltaTime);

	if(Asteroid::getAsteroidCount() <= 0) {
		++level;
		entityManager.getEntity(SPACESHIP)->SetPosition(Game::getResolution().x/2.0f,Game::getResolution().y/2.0f);
		entityManager.getEntity(SPACESHIP)->SetRotation(0.0f);
		spawnAsteroids(level);
	}

	Spaceship* spaceship = dynamic_cast<Spaceship*>(Singleplayer::entityManager.getEntity(Singleplayer::SPACESHIP));
	if(spaceship) {
		if(spaceship->getLifes() <= 0) {
			return Game::GAME_OVER;
		}
	}

	return Game::SINGLEPLAYER;
}

void Singleplayer::draw() {
	renderWindow.Draw(background);
	entityManager.draw(renderWindow);
	hud.draw(renderWindow);
}

void Singleplayer::spawnAsteroids(int lvl) {

	for(int i = 0; i < lvl; ++i) {

		// choose a random position
		sf::Vector2f pos;
		do {
			pos.x = thor::Random(0.0f,float(Game::getResolution().x));
			pos.y = thor::Random(0.0f,float(Game::getResolution().y));
		} while(saveZone.Contains(pos)); // make sure the pos is not in the save zone

		// choose a random velocity
		sf::Vector2f speed;
		if(thor::Random(0,1) == 1) {
			speed.x = thor::Random(25.0f,50.0f);
		} else {
			speed.x = thor::Random(-25.0f,-50.0f);
		}
		if(thor::Random(0,1) == 1) {
			speed.y = thor::Random(25.0f,50.0f);
		} else {
			speed.y = thor::Random(-25.0f,-50.0f);
		}

		entityManager.add(new Asteroid(pos,speed,Asteroid::BIG, thor::Random(0.0f,360.0f)));
	}
}
