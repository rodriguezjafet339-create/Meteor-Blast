#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>
#include <MenuUI.h>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>

//game engine class?
class Game
{
    MenuUI menuUI;
    public:
        //variables
        //window
       sf::RenderWindow& window;
       sf::Event event;

       //mouse positions
       sf::Vector2i mousePosWindow;
       sf::Vector2f mousePosView;

       //game logic
       bool endGame;
       unsigned points;
       int maxHealth;
       int health;
       float enemySpawnTimer;
       float enemySpawnTimerMax;
       int maxEnemies;
       bool mouseHeld;
       bool isPaused;

       //timing
       sf::Clock gameClock;
       sf::Clock deltaClock;
       float baseEnemySpeed;
       float currentSpeed;
       sf::Clock pauseClock;
       sf::Time totalPausedTime;


       //resources
       sf::Font font;

       //text holders
       sf::Text uiText;

       //game objects
       std::vector <sf::CircleShape> enemies;
       sf::CircleShape enemy;
       //initialization funcs

       void inVariables();
       void inFonts();
       void inText();
       void inEnemies();


    public:
        //constructors and destructors
        Game(sf::RenderWindow& window);
        virtual ~Game();

      //accessors
      const bool running () const;
      const bool getEndGame () const;

    //Functions
    void startGame ();

    void spawnEnemy ();
    void pollEvents();
    void updateMP();

    void updateText();
    void updateEnemies(float dt);
    void update();

    void renderText (sf::RenderTarget& target);
    void renderEnemies(sf::RenderTarget& target);
    void render();


};

#endif // GAME_H
