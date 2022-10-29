#pragma once

#include <iostream>
#include <ctime>
#include <vector>

#include "Player.hpp"
#include "SwagBall.hpp"

class Game{
public:
    Game();
    ~Game();

    void update();
    void render();

    void pollEvents();

//Accessors
    const bool getGameOver() const;

private:
//Functions
    void initWindow();
    void initVariables();
    void spawnBalls();

//Modifiers
    void updateCollision();

private:
    sf::RenderWindow* window;
    sf::VideoMode vm;
    sf::Event sfmlEvent;

    bool gameOver;

    Player player;

    std::vector<SwagBall> balls;
    float spawnTimerMax;
    float spawnTimer;
    size_t maxBalls;
};