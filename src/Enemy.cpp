#include "Enemy.hpp"

Enemy::Enemy(float _posx, float _posy){
    this->initShape();
    this->initVariables();
    shape.setPosition(_posx, _posy);
}

void Enemy::initShape(){
    shape.setRadius(rand() % 100 + 20);
    shape.setFillColor(sf::Color(
        (rand() % 150 + 50), 
        (rand() % 150 + 50), 
        (rand() % 150 + 50),
        255)
    );
}

void Enemy::initVariables(){
    type    = 0;
    hpMax   = 10;
    hp      = 0;
    points  = 5;
    damage  = 1;
}

void Enemy::update(){
    shape.move(0.f, 3.f);
}

void Enemy::render(sf::RenderTarget* target){
    target->draw(shape);
}

sf::FloatRect Enemy::getBounds() const{
    return shape.getGlobalBounds();
}

Enemy::~Enemy(){}