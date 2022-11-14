#pragma once

#include "Player.hpp"
#include "Bullet.hpp"
#include "Enemy.hpp"
#include <map>
#include <sstream>
#include <string>

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
    void initFonts();
    void initGUI();

    //Player stuff
    void updatePlayerMovment();
    void updatePlayerCollision();

    void updatePollEvents();
    void updateInput();

    //Enemies
    void updateEnemies();
    void updateCombat();

    //Bullets
    void updateBullets();

    void updateWorld();
    void updateGUI();

    void renderGUI();

    void restartGame();
private:
    //Window
    sf::RenderWindow* window;
    sf::VideoMode vm;

    //Events
    sf::Event ev;
    bool gameOver;

    //Player
    Player* p;
    size_t points;

    //PlayerGUI
    sf::RectangleShape playerHpBar;
    sf::RectangleShape playerHpBarBack;

    //Enemies
    std::vector<Enemy*> enemies;
    float spawnTimer;
    float spawnTimerMax;

    //Resources
    std::map<std::string, sf::Texture*> textures;
    std::vector<Bullet*> bullets;
    sf::Texture _background;
    sf::Sprite background;
    sf::Font font;
    sf::Text pointText;
    sf::Text gameOverText;

};