#include "Player.hpp"

Player::Player(float x, float y){
    this->shape.setPosition(x, y);

    initVariables();
    initShape();
}

Player::~Player(){}

void Player::initShape(){
    this->shape.setFillColor(sf::Color::Green);
    this->shape.setSize(sf::Vector2f(50.f, 100.f));
}

void Player::initVariables(){
    this->speed = 10.f;
    this->points = 0;
    this->HP = 10;
}

void Player::render(sf::RenderTarget* target){
    target->draw(this->shape);
}

void Player::update(sf::RenderTarget* target){
    //Window bounds collision
    this->updateInput();
    this->updateWindowBoundsCollision(target);
}


void Player::updateInput(){
//Keyboard input
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        shape.move(-speed, 0.f);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        shape.move(speed, 0.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        shape.move(0.f, -speed);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        shape.move(0.f, speed);
    }
}

void Player::updateWindowBoundsCollision(const sf::RenderTarget* target){
    //Left
    if(shape.getGlobalBounds().left <= 0.f){
        shape.setPosition(0.f, shape.getGlobalBounds().top);
    }

    //Right
    if(shape.getGlobalBounds().left + shape.getGlobalBounds().width >= target->getSize().x){
        shape.setPosition(target->getSize().x - shape.getGlobalBounds().width,
        shape.getGlobalBounds().top);
    }

    //Top
    if(shape.getGlobalBounds().top <= 0.f){
        shape.setPosition(shape.getGlobalBounds().left, 0.f);
    }

    //Bottom
    if(shape.getGlobalBounds().top + shape.getGlobalBounds().height >= target->getSize().y){
        shape.setPosition(shape.getGlobalBounds().left,
        target->getSize().y - shape.getGlobalBounds().height);
    }
}

const sf::RectangleShape& Player:: getShape() const {
    return shape;
}