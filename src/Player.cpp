#include "Player.hpp"

Player::Player()
{
    initVariables();
    initTextures();
    initSprite();
    initAnimation();
}

void Player::initTextures()
{
    if (!texture_sheet.loadFromFile("../assets/player_sheet.png"))
        std::cout << "ERROR::PLAYYER::Could not load the player sheet.\n";
}
void Player::initSprite()
{
    sprite.setTexture(texture_sheet);
    currentFrame = (sf::IntRect(0, 0, 40, 50));
    sprite.setTextureRect(currentFrame);
    sprite.setScale(1.5f, 1.5f);
    sprite.setPosition(10.f, 150.f);
}
void Player::initVariables()
{
    speed = 2.5f;
    velocityMax = 8.f;
    velocityMin = 0.6f;
    acceleration = 1.f;
    drag = 0.9f;
    gravity = 1.2f;
    velocityMaxY = 250.f;
    jumpForce = 45.f;
    falling = false;
    prevY = sprite.getPosition().y;
    onPlatform = false;
}

void Player::initAnimation()
{
    IdleTimer.restart();
    RunTimer.restart();
    JumpTimer.restart();
    animState = IDLE;
}

void Player::update()
{
    this->updateMovment();
    this->updatePhysics();
    this->updateAnimation();

    std::cout << "Player left: " << sprite.getGlobalBounds().left << ' ' << "Player top: " << sprite.getGlobalBounds().top << "\n";

    std::cout << "Player width: " << sprite.getGlobalBounds().width << ' ' << "Player height: " << sprite.getGlobalBounds().height << "\n";

    std::cout << "Origin: " << sprite.getOrigin().x << ' ' << sprite.getOrigin().y << '\n';
    std::cout << "velocity: " << velocity.x << ' ' << velocity.y << '\n';
    std::cout << "Player Y: " << sprite.getPosition().y << '\n';

    std::cout << "Falling: " << (falling) << '\n';

    std::cout << "OnPlatform " << onPlatform << '\n';

    std::cout << "animation state: " << animState << animState << '\n';
}

void Player::updateAnimation()
{
    if (animState == IDLE)
    {
        if (IdleTimer.getElapsedTime().asSeconds() >= 0.2f)
        {
            currentFrame.top = 0.f;
            currentFrame.left += 40.f;
            if (currentFrame.left >= 160.f)
                currentFrame.left = 0;

            sprite.setTextureRect(currentFrame);
            IdleTimer.restart();
        }
    }
    else if (animState == RIGHT && onPlatform)
    {
        if (RunTimer.getElapsedTime().asSeconds() >= 0.05f)
        {
            currentFrame.top = 50.f;
            currentFrame.left += 40.f;
            if (currentFrame.left >= 360.f)
                currentFrame.left = 0;

            sprite.setTextureRect(currentFrame);
            RunTimer.restart();
        }
        sprite.setOrigin(0.f, 0.f);
        sprite.setScale(1.5f, 1.5f);
    }
    else if (animState == LEFT && onPlatform)
    {
        if (RunTimer.getElapsedTime().asSeconds() >= 0.05f)
        {
            currentFrame.top = 50.f;
            currentFrame.left += 40.f;
            if (currentFrame.left >= 360.f)
                currentFrame.left = 0;

            sprite.setTextureRect(currentFrame);
            RunTimer.restart();
        }
        sprite.setOrigin(sprite.getGlobalBounds().width / 1.5f, 0.f);
        sprite.setScale(-1.5f, 1.5f);
    }
    else if (animState == JUMPNIG)
    {

        currentFrame.top = 100.f;
        currentFrame.left += 40.f;
        if (currentFrame.left >= 80.f)
        {
            currentFrame.left = 0;
            sprite.setTextureRect(currentFrame);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                sprite.setOrigin(sprite.getGlobalBounds().width / 1.5f, 0.f);
                sprite.setScale(-1.5f, 1.5f);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                sprite.setOrigin(0.f, 0.f);
                sprite.setScale(1.5f, 1.5f);
            }
        }
    }
    else if (animState == FALLING)
    {
        currentFrame.top = 200.f;
        currentFrame.left += 40.f;
        if (currentFrame.left >= 80.f)
        {
            currentFrame.left = 0.f;
            sprite.setTextureRect(currentFrame);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                sprite.setOrigin(sprite.getGlobalBounds().width / 1.5f, 0.f);
                sprite.setScale(-1.5f, 1.5f);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                sprite.setOrigin(0.f, 0.f);
                sprite.setScale(1.5f, 1.5f);
            }
        }
    }
}

void Player::updateMovment()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        move(-1.f, 0.f);
        animState = LEFT;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        move(1.f, 0.f);
        animState = RIGHT;
    }
    else if (onPlatform)
    {
        animState = IDLE;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && (onPlatform))
    {
        move(0.f, -1.f);
        animState = JUMPNIG;
    }
}

void Player::updatePhysics()
{
    prevY = sprite.getPosition().y;
    // Gravity

    velocity.y += 1.0 * gravity;
    if (std::abs(velocity.y) > velocityMaxY)
        velocity.y = velocityMaxY * ((velocity.y < 0.f) ? -1.f : 1.f);
    velocity.y *= drag;

    // deceleration
    velocity.x *= drag;

    // limit deceleration
    if (std::abs(velocity.x) < velocityMin)
        velocity.x = 0.f;

    if (std::abs(velocity.y) < velocityMin)
        velocity.y = 0.f;

    sprite.move(velocity);

    // Falling?
    if (sprite.getPosition().y > prevY && onPlatform == false)
    {
        falling = true;
        animState = FALLING;
    }
    else
    {
        falling = false;
    }
}

void Player::move(const float _x, const float _y)
{
    // Acceleration
    velocity.x += _x * acceleration;
    velocity.y += _y * jumpForce;

    // Limit velocity
    if (std::abs(velocity.x) > velocityMax)
        velocity.x = velocityMax * ((velocity.x < 0.f) ? -1.f : 1.f);
    if (std::abs(velocity.y) > velocityMaxY)
        velocity.y = velocityMaxY;
}

void Player::render(sf::RenderTarget *target)
{
    target->draw(sprite);
}

Player::~Player() {}

const sf::FloatRect Player::getGlobalBounds() const
{
    return sprite.getGlobalBounds();
}

void Player::setPosition(const float _x, const float _y)
{
    sprite.setPosition(_x, _y);
}

void Player::setPosition(const sf::Vector2f _pos)
{
    sprite.setPosition(_pos);
}

void Player::setVelocity(const sf::Vector2f _vel)
{
    this->velocity = _vel;
}

void Player::setFalling(bool _val)
{
    falling = _val;
}

void Player::resetVelocityY()
{
    velocity.y = 0.f;
}

void Player::setOnPlatform(bool _val)
{
    onPlatform = _val;
}

const sf::Vector2f Player::getPosition() const
{
    return sprite.getPosition();
}