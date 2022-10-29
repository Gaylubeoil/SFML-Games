#pragma once

#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

class SwagBall{
public:
    SwagBall(const sf::RenderWindow* window);
    ~SwagBall() = default;

    void update();
    void render(sf::RenderTarget* target);

    const sf::CircleShape& getShape() const;

private:
    sf::CircleShape shape;

    void initShape(const sf::RenderWindow* window);

};