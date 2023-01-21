#pragma once
#include "Window.hpp"
#include "Player.hpp"
#include "Tilemap.hpp"

class Game
{
public:
    Game();
    ~Game();

    void run();

private:
    // Init
    void initVariables();
    void initWindow();
    void initPlayer();
    void initTilemap();
    void initView();

    // Update
    void update();
    void updatePollEvents();
    void updatePlayer();
    void updateCollision();
    void updateMousePos();
    void updateLine();
    void updateView();

    /*
        Updates the Delta time variable with the time it
        takes to update and render one frame.
    */
    void updateDeltaTime();

    // Render
    void render();
    void renderPlayer();

private:
    // Window
    Window *window;
    sf::Event event;

    // Fps
    float deltaTime;
    sf::Clock dtClock;

    // Player
    Player *player;

    // Mouse
    sf::Vector2i mousePosView;
    sf::Vector2f mousePos;

    // Line
    sf::VertexArray *line;
    sf::Vertex p1;
    sf::Vertex p2;

    // Game View
    sf::View view;

    // Tilemap
    Tilemap tilemap;
};