#include "Game.hpp"

// Public
Game::Game()
{
    this->initStartScreen();
    this->initVariables();
    this->initWindow();
    this->initEnemies();
    this->initFonts();
    this->initText();
}

void Game::restartGame(){
    this->gameOver = false;
    this->uiText.setPosition(10, 10);
    this->points = 0;
    this->health = 10;
    this->enemies.clear();
    this->startScreen = true;
}

void Game::pollEvents()
{
    // Event polling
    while (this->window->pollEvent(this->ev))
    {
        switch (this->ev.type)
        {
        case sf::Event::Closed:
            this->window->close();
            break;

        case sf::Event::KeyPressed:
            if (this->ev.key.code == sf::Keyboard::Escape)
                this->window->close();
            else if (this->ev.key.code == sf::Keyboard::X)
                if (gameOver = true)
                    restartGame();
            break;

        }
    }
}

void Game::updateMousePos()
{
    this->mousePos = sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(this->mousePos);
}

void Game::updateEnemies()
{
    if (enemies.size() < maxEnemies)
    {
        if (enemySpawnTimer >= enemySpawnTimerMax)
        {
            spawnEnemy();
            enemySpawnTimer = 0.f;
        }
        else
        {
            enemySpawnTimer += 1.f;
        }
    }

    for (uint16_t i = 0; i < enemies.size(); ++i)
    {
        enemies[i].move(0.f, this->enemySpeed);
        if (enemies[i].getPosition().y >= this->vm.height)
        {
            if (enemies[i].getFillColor() != sf::Color::Green)
                this->health -= 1;
            enemies.erase(enemies.begin() + i);
        }
    }
    
    increaseDifficultyTimer--;
    if (increaseDifficultyTimer == 0){
        increaseDifficultyTimer = 100.f;
        if (enemySpawnTimerMax > 0){
            enemySpawnTimerMax -= 0.5f;
        }
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (mouseHeld == false)
        {
            mouseHeld = true;
            bool deleted = false;
            for (size_t i = 0; i < enemies.size() && deleted == false; ++i)
            {
                if (enemies[i].getGlobalBounds().contains(mousePosView))
                {
                    enemies[i].setFillColor(sf::Color::Green);
                    deleted = true;
                    points += 1;
                }
            }
        }
    }
    else
    {
        mouseHeld = false;
    }
}

void Game::updateText(){
    if(startScreen){
        uiText.setPosition(200, 50);
        this->uiText.setString("Choose Difficulty!");
    }
    else if (gameOver){
        this->uiText.setPosition(
            this->vm.width / 4,
            this->vm.height / 2
        );
        this->uiText.setString("Game Over! Wanna try again?\n\tPress X to restart.");
    }
    else {
        uiText.setPosition(10, 10);
        std::stringstream ss;
        ss << "Points: " << this->points << "\n"
            << "Health: " << this->health << "\n"
            << "Spawn speed: " << this->enemySpawnTimerMax;


        this->uiText.setString(ss.str());
    }
}

void Game::updateStartScreen(){
    this->updateText();
    enemies.clear();
    sf::RectangleShape easy;
    easy.setFillColor(sf::Color::Green);
    easy.setPosition(150, 100);
    easy.setSize(sf::Vector2f(50.f, 50.f));


    sf::RectangleShape med;
    med.setFillColor(sf::Color::Yellow);
    med.setPosition(250, 100);
    med.setSize(sf::Vector2f(50.f, 50.f));

    sf::RectangleShape hard;
    hard.setFillColor(sf::Color::Red);
    hard.setPosition(350, 100);
    hard.setSize(sf::Vector2f(50.f, 50.f));

    df.push_back(med);
    df.push_back(easy);
    df.push_back(hard);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        for(auto& rect: df){
            if (rect.getGlobalBounds().contains(mousePosView)){
                if (rect.getFillColor() == sf::Color::Green){
                    this->difficulty = Difficulty::Easy;
                }
                else if (rect.getFillColor() == sf::Color::Yellow){
                    this->difficulty = Difficulty::Medium;
                }
                else if (rect.getFillColor() == sf::Color::Red){
                    this->difficulty = Difficulty::Hard;
                }
                startScreen = false;
                df.clear();

            }
        }
    }
    if (difficulty == Difficulty::Easy){
        this->enemySpawnTimerMax = 80.f;
        this->enemySpeed = 3.f;
    }
    else if (difficulty == Difficulty::Medium){
        this->enemySpawnTimerMax = 55.f;
                this->enemySpeed = 5.f;
    }
    else {
        this->enemySpawnTimerMax = 35.f;
                this->enemySpeed = 8.f;
    }
    
}

void Game::update()
{
    this->pollEvents();

    if (startScreen){
        this->updateMousePos();
        this->updateStartScreen();
    }

    if (!gameOver && !startScreen){
        this->updateMousePos();
        this->updateEnemies();
        this->updateText();
    }

    if (health <= 0) {
        gameOver = true;
    }

    if (gameOver == true){
        this->updateText();
    }
}

void Game::render()
{
    /*
        @return void
        - clear old frame;
        - render objects;
        - display frame in window;
        Renders the game objects.
    */

    this->window->clear();
    this->renderStartScreen(*this->window);
    this->renderEnemies(*this->window);

    this->renderText(*this->window);
    this->window->display();
}

void Game::renderEnemies(sf::RenderTarget& target)
{
    for (auto &e : enemies)
        target.draw(e);
}

void Game::renderText(sf::RenderTarget& target){
    target.draw(this->uiText);
}

void Game::renderStartScreen(sf::RenderTarget& target){
    for (auto& diff: df){
        target.draw(diff);
    }
}

void Game::spawnEnemy()
{
    /*
        @return void

        Spawns enemies and sets their colors and positions.
        -Sets a rand() position.
        -Sets a rand() color.
        -Adds the enemy to the enemies vector.
    */

    enemy.setPosition(
        static_cast<float>(rand() % static_cast<int>(window->getSize().x - enemy.getSize().x)),
        0.f);

    enemy.setFillColor(sf::Color(150, 20, 226, 255));
    //enemy.setRotation(rand() % 45);

    enemies.push_back(enemy);
}

const bool Game::getWindowIsOpen() const
{
    return this->window->isOpen();
}

const bool Game::getGameOverConst() const {
    return gameOver;
}

// Private
void Game::initVariables()
{
    window = nullptr;

    health = 10;
    points = 0;

    mouseHeld = false;
    enemySpawnTimer = this->enemySpawnTimerMax;
    maxEnemies = 100.f;
    increaseDifficultyTimer = 100.f;

    gameOver = false;
}

void Game::initEnemies()
{
    this->enemy.setPosition(50, 50);
    this->enemy.setSize(sf::Vector2f(50.f, 50.f));

    this->enemy.setFillColor(sf::Color::Magenta);
}

void Game::initWindow(){
    this->vm.width = 640;
    this->vm.height = 480;
    this->window = new sf::RenderWindow(vm, "Poggers", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(60);
}

void Game::initFonts(){
    if(!this->font.loadFromFile("Fonts/FFFFORWA.TTF")){
        std::cout << "ERROR::GAME::INITFONTS::Failed to load font!\n";
    }
}

void Game::initText(){
    uiText.setFont(this->font);
    uiText.setCharacterSize(14);
    uiText.setFillColor(sf::Color::White);
    uiText.setStyle(sf::Text::Italic);
    uiText.setString("Uninitialized string");
    uiText.setPosition(10, 10);
}

void Game::initStartScreen(){
    this->startScreen = true;
    this->difficulty = Difficulty::Undef;
}

Game::~Game()
{
    delete this->window;
}

