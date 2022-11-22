#include "Tile.hpp"

const sf::FloatRect Tile::getGlobalBounds() const
{
    return tile.getGlobalBounds();
}

const sf::Vector2f Tile::getPosition() const
{
    return this->tile.getPosition();
}

Tile::Tile(sf::Texture &texture_sheet, sf::IntRect textureRect)
{
    tile.setTexture(texture_sheet);
    tile.setTextureRect(textureRect);
    tile.setScale(2.f, 2.f);
}

void Tile::update() {}

void Tile::render(sf::RenderTarget *target)
{
    target->draw(tile);
}

void Tile::setPos(float _x, float _y)
{
    tile.setPosition(_x, _y);
}