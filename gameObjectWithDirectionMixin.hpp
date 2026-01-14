#pragma once
#include <SFML/Graphics.hpp>

#include "direction.hpp"

using namespace sf;

class GameObjectWithDirectionMixin {
protected:
    Sprite& _sprite;  // Подчеркивание нужно для устранения конфликта имён.
    Direction direction;

    void flipSprite(Direction _direction) {
        if (_direction == direction) {
            return;
        }
        _sprite.setPosition(_sprite.getPosition().x - _direction * _sprite.getGlobalBounds().width, _sprite.getPosition().y);
        _sprite.setScale(_direction * 1.f, 1.f);
        direction = _direction;
    }

public:
    GameObjectWithDirectionMixin(Sprite& sprite, Direction direction = Direction::RIGHT) : _sprite(sprite), direction(direction) {}

};
