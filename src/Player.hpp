#pragma once
#include "PCH.hpp"

// Player animation state
enum PAS
{
    IDLE = 0,
    LEFT,
    RIGHT,
    JUMPNIG,
    FALLING
};

class Player
{
public:
    Player();
    ~Player();

    void update();

    // Render
    void render(sf::RenderTarget *target);

    // Getters
    const sf::FloatRect getGlobalBounds() const;
    const sf::Vector2f getPosition() const;

    // Setters
    void setPosition(const float _x, const float _y);
    void setPosition(const sf::Vector2f _pos);
    void setVelocity(const sf::Vector2f _vel);
    void resetVelocityY();
    void setFalling(bool _val);
    void setOnPlatform(bool _val);

    // Movment
    void move(const float _x, const float _y);

private:
    // Init
    void initVariables();
    void initTextures();
    void initSprite();
    void initAnimation();

    // Update
    void updateAnimation();
    void updatePhysics();
    void updateMovment();

private:
    // Textures and object
    sf::Texture texture_sheet;
    sf::Sprite sprite;

    // Physics
    float speed;
    sf::Vector2f velocity;
    float velocityMax;
    float velocityMin;
    float acceleration;
    float drag;
    float gravity;
    float velocityMaxY;
    float jumpForce;
    sf::Clock JumpTimer;

    bool falling;
    bool onPlatform;

    float prevY;

    // Line

    // Animations and timers
    short animState;
    sf::IntRect currentFrame;

    sf::Clock IdleTimer;
    sf::Clock RunTimer;
};