#pragma once
#include "PCH.hpp"

class Tile
{
public:
    Tile(sf::Texture &texture_sheet, sf::IntRect textureRect);
    ~Tile() = default;

    void update();
    void render(sf::RenderTarget *target);

    const sf::FloatRect getGlobalBounds() const;
    const sf::Vector2f getPosition() const;

    void setPos(float _x, float _y);

private:
private:
    sf::Sprite tile;
};