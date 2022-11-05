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

void Game::handle_hsc(Difficulty x){
    if (x == Difficulty::Easy){
            for(size_t i = 0; i < 5; ++i){
                if (points > easy_hsc[i]){
                    easy_hsc.erase(easy_hsc.begin() + i);
                    easy_hsc.push_back(points);
                    break;
                }
            }
            std::sort(easy_hsc.begin(), easy_hsc.end());
        
    }
    else if (x == Difficulty::Medium){
        
            for(size_t i = 0; i < 5; ++i){
                if (points > med_hsc[i]){
                    med_hsc.erase(med_hsc.begin() + i);
                    med_hsc.push_back(points);
                    break;
                }
            }
            std::sort(med_hsc.begin(), med_hsc.end());
        
    }
    else if (x == Difficulty::Hard){
        
            for(size_t i = 0; i < 5; ++i){
                if (points > hard_hsc[i]){
                    hard_hsc.erase(hard_hsc.begin() + i);
                    hard_hsc.push_back(points);
                    break;
                }
            }
            std::sort(hard_hsc.begin(), hard_hsc.end());
        
    }
}

void Game::handle_hsc_text(){
    std::stringstream stream1, stream2, stream3;
    stream1 << "Easy:\n\n";
    for(int i = 4; i >= 0; --i){
        stream1 << easy_hsc[i] << "\n\n";
    }

    hsc_text[0].setPosition(30, 350);
    hsc_text[0].setString(stream1.str());

    stream2 << "Medium:\n\n";
    for(int i = 4; i >= 0; --i){
        stream2 << med_hsc[i] << "\n\n";
    }

    hsc_text[1].setPosition(200, 350);
    hsc_text[1].setString(stream2.str());

    stream3 << "Hard:\n\n";
    for(int i = 4; i >= 0; --i){
        stream3 << hard_hsc[i] << "\n\n";
    }

    hsc_text[2].setPosition(360, 350);
    hsc_text[2].setString(stream3.str());

}

void Game::restartGame(){
    handle_hsc(difficulty);
    handle_hsc_text();

    this->gameOver = false;
    this->uiText.setPosition(10, 10);
    this->points = 0;
    this->health = 10;
    this->enemies.clear();
    this->startScreen = true;
    this->difficulty = Difficulty::Undef;
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
            if (this->ev.key.code == sf::Keyboard::X)
                if (gameOver = true)
                    restartGame();
            if (this->ev.key.code == sf::Keyboard::H){
                this->health += 50;
                this->points += 500;
            }
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
                    if (!(enemies[i].getFillColor() == sf::Color::Green)){
                        enemies[i].setFillColor(sf::Color::Green);
                        deleted = true;
                        points += 1;

                    }
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
        uiText.setPosition(155, 50);
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
    handle_hsc_text();
    this->updateText();
    enemies.clear();
    sf::RectangleShape easy;
    easy.setFillColor(sf::Color::Green);
    easy.setPosition(115, 100);
    easy.setSize(sf::Vector2f(50.f, 50.f));


    sf::RectangleShape med;
    med.setFillColor(sf::Color::Yellow);
    med.setPosition(215, 100);
    med.setSize(sf::Vector2f(50.f, 50.f));

    sf::RectangleShape hard;
    hard.setFillColor(sf::Color::Red);
    hard.setPosition(315, 100);
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
    
    if (startScreen){
        for(int i = 0; i < 3; ++i){
         target.draw(this->hsc_text[i]);
        }

    }
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
    // enemy.setRotation(rand() % 45);

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

    for(size_t i = 0; i < 5; ++i){
        easy_hsc.push_back(0);
        med_hsc.push_back(0);
        hard_hsc.push_back(0);
    }

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
    this->vm.width = 480;
    this->vm.height = 640;
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

    for(int i = 0; i < 3; ++i){
        hsc_text[i].setFont(font);
        hsc_text[i].setCharacterSize(14);
        hsc_text[i].setFillColor(sf::Color::White);
        hsc_text[i].setStyle(sf::Text::Italic);
        hsc_text[i].setString("uninit");
        hsc_text[i].setPosition(10, 300);

    }
}

void Game::initStartScreen(){
    this->startScreen = true;
    this->difficulty = Difficulty::Undef;
}

Game::~Game()
{
    delete this->window;
}

