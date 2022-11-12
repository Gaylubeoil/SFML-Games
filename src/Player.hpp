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

    sf::Sprite getSprite() const;
    
    const sf::Vector2f& getPos() const;
    sf::FloatRect getBounds() const;
private:
    void initSprite();
    void initTexture();
    void initVariables();

    void updateAttack();

private:
    sf::Sprite sprite;
    sf::Texture texture;

    float movmentSpeed;

    float attackCooldown;
    float attackCooldownMax;
};