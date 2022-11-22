#include "Game.hpp"

Game::Game()
{
    this->initVariables();
    this->initWindow();
    this->initPlayer();
    this->initTilemap();
}

// Run loop
void Game::run()
{
    while (window->get()->isOpen())
    {
        update();
        render();
    }
}

// Init
void Game::initWindow()
{
    window = new Window(800, 608, "Platformer yea");
}

void Game::initVariables()
{
    p1.color = sf::Color::Magenta;
    p2.color = sf::Color::Magenta;

    line = new sf::VertexArray(sf::Lines, 2);
}

void Game::initPlayer()
{
    player = new Player;
}

void Game::initTilemap()
{
    tilemap.init(window->get());
}

// Update
void Game::update()
{
    this->updatePollEvents();
    this->updatePlayer();
    this->updateCollision();
    tilemap.updateCollision(player);
    this->updateMousePos();
    this->updateLine();
}

void Game::updateLine()
{
    line->resize(2);

    p1.position = sf::Vector2f(player->getPosition().x + player->getGlobalBounds().width / 2,
                               player->getPosition().y + player->getGlobalBounds().height / 2);
    p2.position = mousePos;

    line->append(p1);
    line->append(p2);
}

void Game::updatePollEvents()
{
    while (this->window->get()->pollEvent(event))
    {
        if (event.Event::type == sf::Event::Closed)
        {
            window->get()->close();
        }
        else if (event.Event::type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Escape)
            {
                window->get()->close();
            }
        }
    }
}

void Game::updatePlayer()
{
    player->update();
}

void Game::updateMousePos()
{
    this->mousePosView = sf::Mouse::getPosition(*window->get());
    this->mousePos = window->get()->mapPixelToCoords(this->mousePosView);
}

void Game::updateCollision()
{
    if (player->getPosition().x > window->getWidth())
    {
        player->setPosition(
            -player->getGlobalBounds().width,
            player->getPosition().y);
    }
    else if (player->getPosition().x + player->getGlobalBounds().width < 0)
    {
        player->setPosition(
            window->getWidth(),
            player->getPosition().y);
    }
}

// Render
void Game::render()
{
    window->get()->clear();
    tilemap.render(window->get());

    window->get()->draw(*line);
    renderPlayer();

    window->get()->display();
}

void Game::renderPlayer()
{
    player->render(window->get());
}

Game::~Game()
{
    delete window;
    delete player;
    delete line;
}