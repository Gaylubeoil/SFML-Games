#pragma once

#include <iostream>
#include <ctime>
#include <sstream>
#include <vector>

#include "Player.hpp"
#include "SwagBall.hpp"

class Game{
public:
    Game();
    ~Game();

    void update();
    void render();

    void renderGui(sf::RenderTarget* target);

    void pollEvents();

//Accessors
    const bool getGameOver() const;

private:
//Functions
    void initWindow();
    void initVariables();
    void initFont();
    void initText();
    void spawnBalls();

//Modifiers
    void updateCollision();
    void updateGui();

private:
    sf::RenderWindow* window;
    sf::VideoMode vm;
    sf::Event sfmlEvent;

    bool gameOver;

    Player player;
    size_t points;

    sf::Text guiText;
    sf::Font font;

    std::vector<SwagBall> balls;
    float spawnTimerMax;
    float spawnTimer;
    size_t maxBalls;
};