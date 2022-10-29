#include "SwagBall.hpp"

SwagBall::SwagBall(const sf::RenderWindow* window){
    initShape(window);
}

void SwagBall::update(){

}

void SwagBall::render(sf::RenderTarget* target){
    target->draw(shape);
}

void SwagBall::initShape(const sf::RenderWindow* window){

    shape.setRadius(static_cast<float>(rand() % 50 + 10));
    
    sf::Color color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1, 255);
    shape.setFillColor(color);

    shape.setPosition(sf::Vector2f(
        static_cast<float>(rand() % window->getSize().x - shape.getGlobalBounds().width),
        static_cast<float>(rand() % window->getSize().y - shape.getGlobalBounds().height)
    ));

} 

const sf::CircleShape& SwagBall:: getShape() const{
    return shape;
}