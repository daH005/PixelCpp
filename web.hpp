#pragma once
#include "abstractGameObject.hpp"
#include "images.hpp"

class Web : public AbstractGameObject {
protected:
    void flipImage() {
        sprite.setScale(-1.f, 1.f);
        sprite.move(sprite.getGlobalBounds().width, 0);
    }

public:
    Web(int x, int y, Direction direction) : AbstractGameObject(x, y, ZIndex::WEB) {
        sprite.setTexture(images::web);
        if (direction == Direction::RIGHT) {
            flipImage();
        }
    }
};

