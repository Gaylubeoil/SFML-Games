#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <sstream>

enum class Difficulty {Undef = 0, Easy, Medium, Hard};

class Game{
/*
    Class that acts as a game engine.
    Wrapper class;
*/
public:
    Game();
    virtual ~Game();

    void restartGame();

    void spawnEnemy();

    void pollEvents();
    void update();
    void updateMousePos();
    void updateEnemies();
    void updateText();
    void updateStartScreen();

    void render();
    void renderEnemies(sf::RenderTarget& target);
    void renderText(sf::RenderTarget& target);
    void renderStartScreen(sf::RenderTarget& target);

    const bool getWindowIsOpen() const;
    const bool getGameOverConst() const;

private:
    void initVariables();
    void initWindow();
    void initEnemies();
    void initFonts();
    void initText();
    void initStartScreen();

private:
    //Window
    sf::RenderWindow* window;
    sf::Event ev;
    sf::VideoMode vm;

    //GameObjects
    sf::RectangleShape enemy;
    std::vector<sf::RectangleShape> enemies;

    //MousePosition
    sf::Vector2i mousePos;
    sf::Vector2f mousePosView;

    //GameLogic
    uint points;
    int health;

    float enemySpawnTimer;
    float enemySpawnTimerMax;
    float increaseDifficultyTimer;
    float enemySpeed;
    int maxEnemies;
    bool mouseHeld;

    bool gameOver;
    bool startScreen;
    Difficulty difficulty;
    std::vector<sf::RectangleShape> df;

    //Resources
    sf::Font font;

    //Text
    sf::Text uiText;
};