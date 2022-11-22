#include "Tilemap.hpp"

Tilemap::Tilemap()
{
    if (!tileset.loadFromFile("../assets/grass.png"))
    {
        std::cout << "ERROR::TILEMAP::FAILED TO LOAD \'grass.png\'\n";
    }
    Tile ground(tileset, sf::IntRect(0, 0, 16, 16));
    Tile lPlat(tileset, sf::IntRect(16, 0, 16, 16));
    Tile mPlat(tileset, sf::IntRect(32, 0, 16, 16));
    Tile rPlat(tileset, sf::IntRect(48, 0, 16, 16));

    tiles.push_back(ground);
    tiles.push_back(lPlat);
    tiles.push_back(mPlat);
    tiles.push_back(rPlat);
}

void Tilemap::updateCollision(Player *target)
{

    for (auto &tile : activeTiles)
    {
        if (target->getGlobalBounds().intersects(tile.getGlobalBounds()))
        {
            if (target->getPosition().y < tile.getPosition().y)
            {
                target->setOnPlatform(true);
                target->setPosition(target->getPosition().x, tile.getGlobalBounds().top - target->getGlobalBounds().height + 5);
                break;
            }
        }
        else if (target->getPosition().y + target->getGlobalBounds().height >= 608)
        {
            target->setOnPlatform(true);
        }
        else
        {
            target->setOnPlatform(false);
        }
    }
}

void Tilemap::render(sf::RenderTarget *target)
{
    const int cell_size = 32;
    for (size_t y = 0; y < tiles_vertically; ++y)
    {
        for (size_t x = 0; x < tiles_horizontally; ++x)
        {
            if (output_map[y][x] == TType::Ground)
            {
                tiles[(int)TType::Ground].setPos(cell_size * x, cell_size * y);
                tiles[(int)TType::Ground].render(target);
            }
            else if (output_map[y][x] == TType::lPlatform)
            {
                tiles[(int)TType::lPlatform].setPos(cell_size * x, cell_size * y);
                tiles[(int)TType::lPlatform].render(target);
            }
            else if (output_map[y][x] == TType::mPlatform)
            {
                tiles[(int)TType::mPlatform].setPos(cell_size * x, cell_size * y);
                tiles[(int)TType::mPlatform].render(target);
            }
            else if (output_map[y][x] == TType::rPlatform)
            {
                tiles[(int)TType::rPlatform].setPos(cell_size * x, cell_size * y);
                tiles[(int)TType::rPlatform].render(target);
            }
        }
    }
}

void Tilemap::init(sf::RenderTarget *target)
{

    map_sketch = {
        "                         ",
        "                         ",
        "                         ",
        "                         ",
        "              LMMR       ",
        "                         ",
        "                     LMMR",
        "                         ",
        "                LMMMMR   ",
        "  LMMMMMR                ",
        "                         ",
        "                         ",
        "                         ",
        "            LMMR         ",
        "                         ",
        "                         ",
        "                         ",
        "                         ",
        "GGGGGGGGGGGGGGGGGGGGGGGGG",
    };

    for (size_t y = 0; y < tiles_vertically; ++y)
    {
        for (size_t x = 0; x < tiles_horizontally; ++x)
        {
            if (map_sketch[y][x] == ' ')
            {
                output_map[y][x] = TType::empty;
            }
            else if (map_sketch[y][x] == 'G')
            {
                output_map[y][x] = TType::Ground;
            }
            else if (map_sketch[y][x] == 'L')
            {
                output_map[y][x] = TType::lPlatform;
            }
            else if (map_sketch[y][x] == 'M')
            {
                output_map[y][x] = TType::mPlatform;
            }
            else if (map_sketch[y][x] == 'R')
            {
                output_map[y][x] = TType::rPlatform;
            }
        }
    }

    fillTilesVector();
}

void Tilemap::fillTilesVector()
{
    const int cell_size = 32;
    for (size_t y = 0; y < tiles_vertically; ++y)
    {
        for (size_t x = 0; x < tiles_horizontally; ++x)
        {

            if (output_map[y][x] == TType::Ground)
            {
                tiles[(int)TType::Ground].setPos(cell_size * x, cell_size * y);
                activeTiles.push_back(tiles[(int)TType::Ground]);
            }
            else if (output_map[y][x] == TType::lPlatform)
            {
                tiles[(int)TType::lPlatform].setPos(cell_size * x, cell_size * y);
                activeTiles.push_back(tiles[(int)TType::lPlatform]);
            }
            else if (output_map[y][x] == TType::mPlatform)
            {
                tiles[(int)TType::mPlatform].setPos(cell_size * x, cell_size * y);
                activeTiles.push_back(tiles[(int)TType::mPlatform]);
            }
            else if (output_map[y][x] == TType::rPlatform)
            {
                tiles[(int)TType::rPlatform].setPos(cell_size * x, cell_size * y);
                activeTiles.push_back(tiles[(int)TType::rPlatform]);
            }
        }
    }
}

Tilemap::~Tilemap() {}