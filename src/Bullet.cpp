#include "Bullet.hpp"

Bullet::Bullet(){}

Bullet::Bullet(sf::Texture* _texture, float _dirx, float _diry, float _speed, float _posx, float _posy)
{
    shape.setTexture(*_texture);
    direction.x = _dirx;
    direction.y = _diry;
    speed = _speed;
    shape.setPosition(_posx, _posy);
}

void Bullet::update(){
    shape.move(speed*direction);
}

void Bullet::render(sf::RenderTarget* target){
    target->draw(shape);
}

sf::FloatRect Bullet::getBounds() const {
    return shape.getGlobalBounds();
}
