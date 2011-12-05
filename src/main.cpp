#include "include/Game.hpp"
#include <SFML/System.hpp>
#include <iostream>

using namespace std;

int main() {

    sf::RenderWindow app(sf::VideoMode(600, 500, 32), "SFML Graphics");
    app.UseVerticalSync(true);
    Game game(app,1.0f/120.0f);
    game.startGameLoop();

    return 0;
}
