#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <string>

class Player{
public: 
    Player();
    ~Player();

    void update();
    void render(sf::RenderTarget& target);

    void move(const float dirX, const float dirY);
    bool canAttack();
    bool canTakeDamage();

    sf::Sprite getSprite() const;
    
    const sf::Vector2f& getPos() const;
    sf::FloatRect getBounds() const;
    size_t getHealth() const;

    void setPos(const sf::Vector2f _pos);
    void setPos(float x, float y);
    void setHealth(size_t _health);
private:
    void initSprite();
    void initTexture();
    void initVariables();

    void updateAttack();
    void updateInvincibility();

private:
    sf::Sprite sprite;
    sf::Texture texture;

    float movmentSpeed;
    size_t health;
    float invincibleCooldown;
    float invincibleCooldownMax;

    float attackCooldown;
    float attackCooldownMax;
};