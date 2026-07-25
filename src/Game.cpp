#include "Game.h"
/**To do:
-Probably make this into a full window to avoid the floating window from disappearing when something
click is out of the windows bounds
-integer overflow prevention
*/

//private functions
void Game::inVariables(){
//game logic
this ->endGame = false;
this ->points = 0;
this ->maxHealth = 10;
this ->health = 5;
this ->enemySpawnTimerMax = 0.5f;
this ->enemySpawnTimer = this ->enemySpawnTimerMax;
this ->maxEnemies = 5;
this ->mouseHeld = false;
this ->mouseHeld = sf::Mouse::isButtonPressed(sf::Mouse::Left);
this ->isPaused = false;

//timing
this->baseEnemySpeed = 60.f;
this->currentSpeed = baseEnemySpeed;
this ->totalPausedTime = sf::Time::Zero;
}
//--------------------------------------------------------
void Game::inFonts() {
if(!this ->font.loadFromFile("Fonts/PixelifySans-VariableFont_wght.ttf")){

    std::cout <<"Error in inFonts function"<<"\n";
}
}
//--------------------------------------------------------------
void Game::inText () {
this -> uiText.setFont(this ->font);
this ->uiText.setCharacterSize(24);
this ->uiText.setFillColor(sf::Color::White);
this ->uiText.setString("NONE");
}
//--------------------------------------------------------------
void Game::inEnemies(){
//this ->enemy.setPosition(10.f,10.f);
//this ->enemy.setRadius(50.f);
//this ->enemy.setFillColor(sf::Color::Red);
//this ->enemy.setOutlineColor(sf::Color::Black);
//this ->enemy.setOutlineThickness(1.f);
}

//--------------------------------------------------------------
//constructors|destructors
Game::Game(sf::RenderWindow& window)
: window(window)
{
    //ctor
    this ->inVariables();
    this ->inFonts();
    this ->inText();
    this ->inEnemies();
}
//--------------------------------------------------------------
Game::~Game()
{
    //dtor
}

//--------------------------------------------------------------
//acessors
const bool Game::running () const {
    return this -> window.isOpen();
}
//--------------------------------------------------------------
const bool Game::getEndGame () const {
    return this -> endGame;
}
//--------------------------------------------------------------


//functions
void Game::spawnEnemy () {
this ->enemy.setPosition(
    static_cast<float>(rand() % static_cast<int>(this->window.getSize().x - this->enemy.getRadius())),
    0.f
);

//enemy types (randomized)
int enemyType = rand ()% 4;

switch (enemyType) {
case 0:
    this ->enemy.setFillColor(sf::Color::Red);
    this ->enemy.setRadius(15.f);
    break;
case 1:
    this ->enemy.setFillColor(sf::Color::Magenta);
    this ->enemy.setRadius(25.f);
    break;
case 2:
    this ->enemy.setFillColor(sf::Color::Yellow);
    this ->enemy.setRadius(35.f);
    break;
case 3: //not an enemy, health increase if caught
    this ->enemy.setFillColor(sf::Color::Green);
    this ->enemy.setRadius(10.f);
    break;
default:
    this ->enemy.setFillColor(sf::Color::Blue);
    this ->enemy.setRadius(80.f);
    break;

}


this ->enemies.push_back(this->enemy);


}
//--------------------------------------------------------------
void Game::pollEvents() {
    while (this->window.pollEvent(this->event)) {
        switch (this->event.type) {
            case sf::Event::Closed:
                this->window.close();
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape) {
                    this->window.close();
                }
                if (event.key.code == sf::Keyboard::Space) {
                    isPaused = !isPaused;
                    if (isPaused) {
                        pauseClock.restart();
                    } else {
                        totalPausedTime += pauseClock.getElapsedTime();
                    }
                }
                break;
        }
    }
}
//--------------------------------------------------------------
void Game::updateMP() {
this ->mousePosWindow = sf::Mouse::getPosition(this -> window);
this ->mousePosView = this -> window.mapPixelToCoords(this ->mousePosWindow);
}
//--------------------------------------------------------------

void Game::updateText() {
    std::stringstream ss;
    ss << "Points: " << this->points <<"\n"
       <<"Health: "<< this->health <<"\n"
       <<"Speed: " << this ->currentSpeed <<"\n";
    this -> uiText.setString(ss.str());
}

//--------------------------------------------------------------
void Game::updateEnemies(float dt) {

if (this ->enemies.size() < this->maxEnemies) {
    if (this->enemySpawnTimer >= this->enemySpawnTimerMax) {
        this ->spawnEnemy();
        this->enemySpawnTimer = 0.f; }
    else {
        this->enemySpawnTimer += dt;}
}

// Movement + off-screen cleanup
for (int i = 0; i < this->enemies.size(); i++) {
    this->enemies[i].move(0.f, this->currentSpeed * dt);

        if (this->enemies[i].getPosition().y > this->window.getSize().y) {
            // check color BEFORE erasing
            if (this->enemies[i].getFillColor() != sf::Color::Green) {
                this->health -= 1;
            }
            this->enemies.erase(this->enemies.begin() + i);
            i--; // re-check the element that slid into index i
        }
    }



//check if clicked

if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
    if (this -> mouseHeld == false) {
        this-> mouseHeld = true;
        bool deleted = false;
            for (size_t i = 0;i <this ->enemies.size()&& deleted == false; i ++) {
                if (this -> enemies[i].getGlobalBounds().contains (this ->mousePosView)) {

                //gaining points
                if (this->enemies[i].getFillColor() == sf::Color::Red){
                    this ->points += 6.f;
                } else if (this->enemies[i].getFillColor() == sf::Color::Magenta){
                    this ->points += 4.f;
                } else if (this->enemies[i].getFillColor() == sf::Color::Yellow){
                    this ->points += 2.f;
                } else if (this->enemies[i].getFillColor() == sf::Color::Green){
                    this ->points += 1.f;
                    if (this-> health < this ->maxHealth) {
                    this -> health += 1;
                    }
                }


                deleted = true;
                this ->enemies.erase(this ->enemies.begin() + i);
                }
            }
        }
    }else {
        this ->mouseHeld = false;
    }
}
//--------------------------------------------------------------
void Game::update(){
    this -> pollEvents();

    //time increases 10% every 6 seconds

    float dt = this->deltaClock.restart().asSeconds();
    if (!isPaused){
    float elapsed = (this->gameClock.getElapsedTime() - this->totalPausedTime).asSeconds();
    this->currentSpeed = this -> baseEnemySpeed * (1.0f + (elapsed / 6.f) * 0.1f);


    if (this ->endGame == false) {
    this ->updateMP();
    this ->updateText();
    this ->updateEnemies(dt);
    }

    if (this ->health <= 0) {
        this ->endGame = true;
    }
    }

}
//--------------------------------------------------------------
void Game::startGame() {
    this->deltaClock.restart();
    this->gameClock.restart();
    this->pauseClock.restart();
    this->totalPausedTime = sf::Time::Zero;
}
//--------------------------------------------------------------
void Game::renderText (sf::RenderTarget& target) {
    target.draw(this->uiText);
}

//--------------------------------------------------------------
void Game::renderEnemies(sf::RenderTarget& target) {
for (auto &e : this ->enemies) {

    target.draw(e);


}
}
//--------------------------------------------------------------
void Game::render(){
this -> window.clear ();

//outputting game objects
this ->renderEnemies(this ->window);

this ->renderText(this ->window);

this -> window.display();
}
