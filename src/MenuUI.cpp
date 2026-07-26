#include "MenuUI.h"

void MenuUI::centerTextInShape(sf::Text& text, const sf::Shape& shape) {
    sf::FloatRect tb = text.getLocalBounds();
    text.setOrigin(tb.left + tb.width / 2.f, tb.top + tb.height / 2.f);

    sf::FloatRect sb = shape.getGlobalBounds();
    text.setPosition(sb.left + sb.width / 2.f, sb.top + sb.height / 2.f);
}
//--------------------------------------------------------

void MenuUI::inPlayButton() {
float playButtonWidth = 200.f;
float playButtonHeigth = 100.f;
this ->playButton.setSize(sf::Vector2f(playButtonWidth, playButtonHeigth));
this ->playButton.setFillColor(sf::Color::Green);
this ->playButton.setPosition ((this->window.getSize().x - playButtonWidth)/2, (this->window.getSize().y - playButtonHeigth)/2);

if(!this ->playFont.loadFromFile("Fonts/BitcountGridDouble-Regular.ttf")){
    std::cout <<"Error in inMenu function"<<"\n";
}
this ->playText.setFont(this -> playFont);
this ->playText.setCharacterSize(80);
this ->playText.setFillColor(sf::Color::White);
this ->playText.setString("PLAY");
this ->centerTextInShape(this ->playText, this ->playButton);

}
//--------------------------------------------------------

MenuUI::MenuUI(sf::RenderWindow& window)
: window(window)
{
    //ctor
    this ->inPlayButton();
    this ->inPauseMenu();
}

MenuUI::~MenuUI()
{
    //dtor
}
//--------------------------------------------------------
void MenuUI::updateMP() {
this ->mousePosWindow = sf::Mouse::getPosition(this -> window);
this ->mousePosView = this -> window.mapPixelToCoords(this ->mousePosWindow);
}
//--------------------------------------------------------
void MenuUI::menuEvents() {
while (this->window.pollEvent(this->event)) {
        switch (this->event.type) {
            case sf::Event::Closed:
                this->window.close();
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape) {
                    this->window.close();
                }
                break;
        }
    }
}
//--------------------------------------------------------
void MenuUI::updateMenu() {
this ->menuEvents();
this ->updateMP();

if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (this ->mouseHeld == false) {
                this ->mouseHeld = true;
        if (this -> playButton.getGlobalBounds().contains (this ->mousePosView)) {
            this -> pressedPlay = true;
        }
        }
    } else {
    this ->mouseHeld = false;
    }
}
//--------------------------------------------------------
void MenuUI::renderPlayButton(sf::RenderTarget& target) {
target.draw(this -> playButton);
target.draw(this -> playText);
}
//---------------------------------------------------------
void MenuUI::renderMenu () {
this ->window.clear();
this ->renderPlayButton(this ->window);
this ->window.display();
}
//---------------------------------------------------------

void MenuUI::inPauseMenu () {
float ButtonWidth = 350.f;
float ButtonHeigth = 80.f;
this ->returnToMenuButton.setSize(sf::Vector2f(ButtonWidth, ButtonHeigth));
this ->returnToMenuButton.setFillColor(sf::Color::Green);
this ->returnToMenuButton.setPosition ((this->window.getSize().x - ButtonWidth)/2, (this->window.getSize().y - ButtonHeigth)/2);

if(!this ->returnToMenuFont.loadFromFile("Fonts/BitcountGridDouble-Regular.ttf")){
    std::cout <<"Error in inMenu function"<<"\n";
}
this ->returnToMenuText.setFont(this -> returnToMenuFont);
this ->returnToMenuText.setCharacterSize(30);
this ->returnToMenuText.setFillColor(sf::Color::White);
this ->returnToMenuText.setString("Return to Main Menu");
this ->centerTextInShape(this ->returnToMenuText, this ->returnToMenuButton);
}

void MenuUI::renderReturnToMenuButton(sf::RenderTarget& target) {
target.draw(this->returnToMenuButton);
target.draw (this->returnToMenuText);
}
