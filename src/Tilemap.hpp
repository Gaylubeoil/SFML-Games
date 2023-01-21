#pragma once
#include "Tile.hpp"
#include "Player.hpp"

const size_t tiles_vertically = 19;
const size_t tiles_horizontally = 50;

enum class TType
{
    empty = -1,
    Ground = 0,
    lPlatform,
    mPlatform,
    rPlatform,
    dirt,
    bricks,
};

class Tilemap
{
public:
    Tilemap();
    ~Tilemap();

    void render(sf::RenderTarget *target);
    void init(sf::RenderTarget *target);
    void updateCollision(Player *target);

private:
    void fillTilesVector();

    void updateVerticalCollision(const std::vector<Tile> &activeTiles, Player *target);
    void updateHorizontalCollision(const std::vector<Tile> &activeTiles, Player *target);

private:
    sf::Texture tileset;
    std::vector<Tile> tiles;
    std::array<std::string, tiles_vertically> map_sketch;
    std::array<std::array<TType, tiles_horizontally>, tiles_vertically> output_map;
    std::vector<Tile> activeTiles;
};