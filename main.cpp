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

    while (window.isOpen()) {
        // --- Menu phase ---
        while (window.isOpen() && !menu.pressedPlay) {
            menu.updateMenu();
            menu.renderMenu();
        }

        if (!window.isOpen()) break;

        // --- Game phase ---
        game.startGame();

        while (game.running() && !game.getEndGame() && !game.getReturnToMenu()) {
            game.update();
            game.render();
        }

        if (!window.isOpen()) break;

        // --- Lose / return-to-menu phase ---

        if (game.getEndGame()) {
            menu.resetReturnMainRequest();

            while (window.isOpen() && game.getEndGame() && !menu.getReturnToMenu()) {
                // poll events directly so the window stays responsive
                // (Closed / Escape) even though we're outside game.update()
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        window.close();
                    }
                    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                        window.close();
                    }
                }

                if (!window.isOpen()) break;

                menu.updateReturnButton();

                window.clear();
                menu.renderLoseText(window);
                menu.renderReturnToMenuButton(window);
                window.display();
            }
        }

        if (!window.isOpen()) break;

        if (menu.getReturnToMenu()) {
            // loop back to menu — reset everything for next time
            game.resetGame();
            menu.pressedPlay = false;
            menu.resetReturnMainRequest();

        }
    }

    return 0;
}
