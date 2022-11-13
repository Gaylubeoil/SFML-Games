#include "Game.hpp"

Game::Game() {
    this->initWindow();
    this->initPlayer();
    this->initVariables();
    this->initEnemies();
    this->initTextures();
    this->initFonts();
}

void Game::initWindow() {
    vm.width = 800;
    vm.height = 600;
    window = new sf::RenderWindow(vm, "Lords 'o space", sf::Style::Close | sf::Style::Titlebar);
    window->setFramerateLimit(60);
    window->setVerticalSyncEnabled(false);
}

void Game::initVariables() {
    gameOver = false;
    _background.loadFromFile("../assets/backgr.png");
    background.setTexture(_background);
    background.setPosition(0, 0);
}

void Game::initPlayer() {
    this->p = new Player;
}

void Game::initEnemies() {
    spawnTimerMax = 45.f;
    spawnTimer = spawnTimerMax;
}

void Game::initTextures(){
    //textures.insert();
    textures["BULLET"] = new sf::Texture();
    textures["BULLET"]->loadFromFile("../assets/bullet.png");
}

void Game::initFonts() {
    if (!font.loadFromFile("../fonts/pixelfont.TTF")){
        std::cout << "pixelfont.TTF failed to load. Game.cpp, 44.\n";
    }

}

void Game::run() {
    while (!gameOver)
    {
        update();
        render();
    }
}

void Game::update() {
    this->updatePollEvents();
    this->updatePlayerMovment();
    this->updateInput();
    this->p->update();
    this->updateEnemies();
    this->updateCombat();
    this->updateBullets();
    this->updatePlayerCollision();
    std::cout << "Enemies size: " << enemies.size() << '\n';
    std::cout << "Bullets size: " << bullets.size() << "\n\n";
    std::cout << "Health: " << p->getHealth() << '\n';
}

void Game::updatePlayerMovment(){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        this->p->move(-1.f, 0.f);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        this->p->move(1.f, 0.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        this->p->move(0.f, -1.f);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        this->p->move(0.f, 1.f);
    }
}
void Game::updatePlayerCollision(){
    if (p->getSprite().getGlobalBounds().height < 0){
        p->getSprite().setPosition(
            p->getSprite().getPosition().x,
            0
        );
    }
    
    if (p->getSprite().getGlobalBounds().width < 0){
        p->getSprite().setPosition(
            0,
            p->getSprite().getPosition().y
        );
    }
}
void Game::updateInput() {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && p->canAttack()){
        bullets.push_back(
        new Bullet(textures["BULLET"],
        0.0f,
        -1.f,
        4.f,
        p->getPos().x + p->getBounds().width / 2.f - 2,
        p->getPos().y + 30)
        );
    }
}
void Game::updatePollEvents(){
     while(this->window->pollEvent(ev)){
        if (ev.Event::type == sf::Event::Closed){
            gameOver = true;
            window->close();
        }
        else if (ev.Event::type == sf::Event::KeyPressed){
            if (ev.key.code == sf::Keyboard::Escape){
                gameOver = true;
                window->close();
            }
        }
    }
}
void Game::updateBullets() {

    size_t counter = 0;
    for(auto *bullet : bullets){
        bullet->update();

        //Bullet culling (top of screen)
        if(bullet->getBounds().top + bullet->getBounds().height < -200.f){
            delete bullets.at(counter);
            bullets.erase(bullets.begin() + counter);
            --counter;
         }

        ++counter;
    }
}
void Game::updateEnemies(){
    spawnTimer += 0.5f;
    if (spawnTimer >= spawnTimerMax){
        enemies.push_back(new Enemy(rand() % vm.width - 20.f, -100.f));
        spawnTimer = 0.f;
    }
    for(size_t i = 0; i < enemies.size(); ++i){
        enemies[i]->update();
        
        if (enemies[i]->getBounds().top > vm.height){
            enemies.erase(enemies.begin() + i);
        }
    }
}
void Game::updateCombat() {
    for(size_t i = 0; i < enemies.size(); ++i){
        for (size_t j = 0; j < bullets.size(); ++j){
            if (bullets[j]->getBounds().intersects(enemies[i]->getBounds())){
                delete bullets.at(j);
                delete enemies.at(i);
                bullets.erase(bullets.begin() + j);
                enemies.erase(enemies.begin() + i);
            }
            
        }
    }
    for(size_t i = 0; i < enemies.size(); ++i){
        if (p->getBounds().intersects(enemies[i]->getBounds())){
            delete enemies.at(i);
            enemies.erase(enemies.begin() + i);
            if (p->getHealth() > 1 && p->canTakeDamage()){
                p->setHealth(p->getHealth() - 1);
            }
        }
    }
}

void Game::render() {
    window->clear();
    // clear old frame
    this->window->draw(background);
    

    this->p->render(*this->window);

    for(auto *bullet : bullets){
        bullet->render(this->window);
    }

    for(auto *enemy : enemies){
        enemy->render(this->window);
    }

    // display new frame
    window->display();
}


Game::~Game() {
    delete window;
    delete p;

    for(auto& _texture: textures)
        delete _texture.second;
    
    for(auto* _bullet : bullets)
        delete _bullet;

    for(auto* _enemy: enemies)
        delete _enemy;   
}