#pragma once

#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

enum SwagBallTypes {DEFAULT = 0, DAMAGING, HEALING, NROFTYPES};

class SwagBall{
public:
    SwagBall(const sf::RenderWindow* window, int type);
    ~SwagBall() = default;

    void update();
    void render(sf::RenderTarget* target);

    const sf::CircleShape& getShape() const;

    const int getType() const;

private:
    sf::CircleShape shape;
    int type;

    void initShape(const sf::RenderWindow* window);

};