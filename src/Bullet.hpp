#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

class Bullet{
public:
    Bullet(sf::Texture* _texture, float _dirx, float _diry, float _speed, float _posx, float _posy);
    Bullet();
    ~Bullet() = default;

    void update();
    void render(sf::RenderTarget* target);

    sf::FloatRect getBounds() const;
private:


private:
    sf::Sprite shape;

    sf::Vector2f direction;
    float speed;
};