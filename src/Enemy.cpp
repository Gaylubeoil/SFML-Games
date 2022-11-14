#include "Enemy.hpp"

Enemy::Enemy(float _posx, float _posy){
    this->initVariables();
    this->initShape();
    shape.setPosition(_posx, _posy);
}

void Enemy::initShape(){
    shape.setPointCount(pointCount);
    shape.setRadius(pointCount * 5);
    shape.setFillColor(sf::Color(
        (rand() % 150 + 50), 
        (rand() % 150 + 50), 
        (rand() % 150 + 50),
        255)
    );
}

void Enemy::initVariables(){
    pointCount   = rand() % 8 + 3; //min=3, max=10
    type         = 0;
    hpMax        = 3;
    hp           = hpMax;
    points       = pointCount;
    damage       = pointCount;
    speed        = static_cast<float>(pointCount) - 2.f;

}

void Enemy::update(){
    shape.move(0.f, speed);
}

void Enemy::render(sf::RenderTarget* target){
    target->draw(shape);
}

sf::FloatRect Enemy::getBounds() const{
    return shape.getGlobalBounds();
}


size_t Enemy::getPoints() const {
    return points;
}
Enemy::~Enemy(){}