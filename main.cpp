#include <iostream>
#include <Game.h>
#include <MenuUI.h>
#include <filesystem>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>

sf::Event event;
sf::VideoMode videoMode(500, 950);

sf::RenderWindow window(videoMode, "Meteor Blaster", sf::Style::Titlebar | sf::Style::Close);

void setupWindow() {
    window.setFramerateLimit(60);
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    window.setPosition(sf::Vector2i((desktop.width - videoMode.width) / 2, 0));
}

int main() {

    std::cout << "Working dir: " << std::filesystem::current_path() << std::endl;
    std::srand(static_cast<unsigned>(time(NULL)));
    setupWindow();

    Game game(window);
    MenuUI menu (window);

    while (window.isOpen() && !menu.pressedPlay) {
        menu.updateMenu();
        menu.renderMenu();
    }

    game.startGame();

    while (game.running() && !game.getEndGame()) {
        game.update();
        game.render();

    }
    return 0;
}


