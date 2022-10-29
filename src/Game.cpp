#include "Game.hpp"

// INITIALIZATION //
Game::Game(){
    this->initVariables();
    this->initWindow();
}

void Game::pollEvents(){
    while(this->window->pollEvent(this->sfmlEvent)){
        switch (sfmlEvent.type){
            case sf::Event::Closed:
                this->window->close();
                break;
            case sf::Event::KeyPressed:
                if (sfmlEvent.key.code == sf::Keyboard::Escape)
                    this->window->close();
                break;
                
        }
    }
}

void Game::initWindow(){
    this->vm = sf::VideoMode(800, 600);
    this->window = new sf::RenderWindow(vm, "Poggers", sf::Style::Close | sf::Style::Titlebar);
    this->window->setFramerateLimit(60);
}

void Game::initVariables(){
    this->gameOver = false;

    spawnTimerMax = 10.f;
    spawnTimer = spawnTimerMax;
    maxBalls = 20;
}



// GAME UPDATES //
void Game::update(){
    this->pollEvents();

    this->spawnBalls();
    this->player.update(this->window);
    this->updateCollision();

}

void Game::updateCollision(){
    for(size_t i = 0; i < balls.size(); ++i){
        if(player.getShape().getGlobalBounds().intersects(balls[i].getShape().getGlobalBounds())){
            balls.erase(balls.begin() + i);

        }
    }
}

// RENDERING //
void Game::render(){
    this->window->clear();

    for(auto i : balls){
        i.render(this->window);
    }

    this->player.render(this->window);
    this->window->display();
}

// ACCESSORS //
const bool Game::getGameOver() const {
    return this->window->isOpen();
}

// MODIFIERS //
void Game::spawnBalls(){
    if (spawnTimer < spawnTimerMax){
        spawnTimer++;
    }
    else {
        if (balls.size() < maxBalls){
            spawnTimer = 0.f;
            balls.push_back(SwagBall(window));
        }
    }
}



Game::~Game(){
    delete window;
}