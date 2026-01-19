#pragma once
#include <SFML/Graphics.hpp>

#include "direction.hpp"

using namespace sf;

class GameObjectWithDirectionMixin {
protected:
    Sprite& _sprite;  // Подчеркивание нужно для устранения конфликта имён.
    Direction direction;

    // Предполагается, что по умолчанию текстуры направлены вправую сторону!
    void flipSprite(Direction _direction) {
        if (_direction == direction) {
            return;
        }
        _sprite.setScale(_direction * 1.f, 1.f);
        direction = _direction;
        updateOrigin();
    }
    
    // Если персонаж повёрнут влево, то при изменении размеров текстуры последующий вызов updateOrigin строго необходим!
    void updateOrigin() {
        _sprite.setOrigin(_sprite.getLocalBounds().width * (direction == Direction::LEFT ? 1.f : 0), 0);
    }

public:
    GameObjectWithDirectionMixin(Sprite& sprite, Direction direction = Direction::RIGHT) : _sprite(sprite), direction(direction) {}

};
