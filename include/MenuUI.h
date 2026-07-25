#ifndef MENUUI_H
#define MENUUI_H

#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>

class MenuUI
{
    public:
       sf::RenderWindow& window;
       sf::Event event;

       sf::RectangleShape playButton;
       sf::Text playText;
       sf::Font playFont;

       //mouse positions
       sf::Vector2i mousePosWindow;
       sf::Vector2f mousePosView;

       bool pressedPlay = false;
       bool mouseHeld = false;

        MenuUI(sf::RenderWindow& window);
        virtual ~MenuUI();

        void inPlayButton();
        void centerTextInShape(sf::Text& text, const sf::Shape& shape);
        void renderPlayButton (sf::RenderTarget& target);
        void updateMP();
        void menuEvents ();
        void renderMenu ();
        void updateMenu ();
};

#endif // MENUUI_H
