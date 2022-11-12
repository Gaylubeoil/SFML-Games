#include "Player.hpp"

Player::Player(){
    initTexture();
    initSprite();
    initVariables();
}

void Player::initVariables(){
    movmentSpeed = 10.f;
    attackCooldownMax = 30.f;
    attackCooldown = attackCooldownMax;

}

void Player::initSprite(){
    //Set the texture to the sprite
    sprite.setTexture(texture);

    //Resize the sprite
    //Setting to -1.f flips the sprite
    //These numbers are a percent, and not an actual scale therefore 1 stands for 100%
    sprite.scale(1.f, 2.f);
}

void Player::initTexture(){
    //Load from file
    if(!texture.loadFromFile("../assets/ship.png")){
        std::cout << "FAILED TO LOAD ASSET \"ship.png\", Player.cpp, 16\n";
    }
    
}

bool Player::canAttack(){
    if (attackCooldown >= attackCooldownMax){
        attackCooldown = 0.f;
        return true;
    }
    return false;
}

void Player::update(){
    updateAttack();
}

 void Player::updateAttack(){
    if (attackCooldown < attackCooldownMax){
        attackCooldown += 0.5f;
    }
    
 }

sf::Sprite Player::getSprite() const{
    return this->sprite;
    }

void Player::render(sf::RenderTarget& target){
    target.draw(sprite);
}

void Player::move(const float dirX, const float dirY){
    sprite.move(movmentSpeed*dirX, movmentSpeed*dirY);
}

const sf::Vector2f& Player::getPos() const{
    return sprite.getPosition();
}

sf::FloatRect Player::getBounds() const {
    return sprite.getGlobalBounds();
}

Player::~Player(){

}