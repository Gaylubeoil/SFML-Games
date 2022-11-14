#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Enemy{
public:
    Enemy(float _posx, float _posy);
    ~Enemy();

    void render(sf::RenderTarget* target);
    void update();

    sf::FloatRect getBounds() const;
    size_t getPoints() const;
private:
    void initVariables();
    void initShape();


private:
    sf::CircleShape shape;
    size_t hp;
    size_t hpMax;
    size_t damage;
    size_t points;
    size_t type;
    size_t pointCount;
    float speed;


};