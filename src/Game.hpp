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

    // Update
    void update();
    void updatePollEvents();
    void updatePlayer();
    void updateCollision();
    void updateMousePos();
    void updateLine();

    // Render
    void render();
    void renderPlayer();

private:
    // Window
    Window *window;
    sf::Event event;

    // Player
    Player *player;

    // Mouse
    sf::Vector2i mousePosView;
    sf::Vector2f mousePos;

    // Line
    sf::VertexArray *line;
    sf::Vertex p1;
    sf::Vertex p2;

    // Tilemap
    Tilemap tilemap;
};