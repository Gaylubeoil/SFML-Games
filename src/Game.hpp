#pragma once

#include "Player.hpp"
#include "Bullet.hpp"
#include "Enemy.hpp"
#include <map>

class Game{
public:
    Game();
    ~Game();

    //Functions
    void run();
    void update();
    void render();


private:
    //Init
    void initWindow();
    void initVariables();
    void initPlayer();
    void initEnemies();
    void initTextures();

    //Player stuff
    void updatePlayerMovment();
    void updatePlayerCollision();

    void updatePollEvents();
    void updateInput();

    //Enemies
    void updateEnemies();

    //Bullets
    void updateBullets();

private:
    //Window
    sf::RenderWindow* window;
    sf::VideoMode vm;

    //Events
    sf::Event ev;
    bool gameOver;

    //Player
    Player* p;

    //Enemies
    std::vector<Enemy*> enemies;
    float spawnTimer;
    float spawnTimerMax;

    //Resources
    std::map<std::string, sf::Texture*> textures;
    std::vector<Bullet*> bullets;
};