#pragma once

#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

class Player{
public:
    Player(float x = 0.f, float y = 0.f);
    ~Player();

    void update(sf::RenderTarget* target);
    void render(sf::RenderTarget* target);

    const sf::RectangleShape& getShape() const;

private:
    void updateInput();
    void updateWindowBoundsCollision(const sf::RenderTarget* target);

    void initVariables();
    void initShape();

    

private:
    sf::RectangleShape shape;
    float speed;

    size_t HP;
    const size_t HP_MAX = 10;
    size_t points;


};