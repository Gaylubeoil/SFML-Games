#include "Game.hpp"

// INITIALIZATION //
Game::Game(){
    this->initVariables();
    this->initWindow();
    this->initFont();
    this->initText();
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
                else if (sfmlEvent.key.code == sf::Keyboard::R){
                    if (gameOver){
                        gameOver = false;
                    }
                }
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
    points = 0;

}

void Game::initFont() {
    if (!font.loadFromFile("../fonts/Minecraft.ttf")){
        std::cout << "GAME::INITFONT::LOADFROMFILE Font not loaded successfully!\n";
    }
}

void Game::initText() {
    guiText.setFont(font);
    guiText.setFillColor(sf::Color::White);
    guiText.setCharacterSize(24);
    guiText.setString("Test");

}



// GAME UPDATES //
void Game::update(){
    this->pollEvents();
    
    if (gameOver){
        return;
    }

    this->spawnBalls();
    this->player.update(this->window);
    this->updateCollision();
    this->updateGui();

}

void Game::updateCollision(){
    for(size_t i = 0; i < balls.size(); ++i){
        if(player.getShape().getGlobalBounds().intersects(balls[i].getShape().getGlobalBounds())){
            switch(balls[i].getType()){
                case SwagBallTypes::DEFAULT: points++; break;
                case SwagBallTypes::DAMAGING: player.takeDamage(1); break;
                case SwagBallTypes::HEALING: player.gainHealth(1); break;
            }

            balls.erase(balls.begin() + i);

            if (player.getHp() == 0){
                player.die();
                gameOver = true;
            }
        }
    }
}

void Game::updateGui(){

    std::stringstream ss;
    ss << "Points: " << points << std::endl 
        << "Health: " << player.getHp() << '/' << player.getHpMAX() << std::endl;
    guiText.setString(ss.str());
}

// RENDERING //
void Game::render(){
    this->window->clear();

    for(auto i : balls){
        i.render(this->window);
    }

    this->player.render(this->window);

    this->renderGui(this->window);
    this->window->display();
}

void Game::renderGui(sf::RenderTarget* target){
    target->draw(guiText);
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
            int type = rand() % SwagBallTypes::NROFTYPES;
            balls.push_back(SwagBall(window, type));
        }
    }
}



Game::~Game(){
    delete window;
}