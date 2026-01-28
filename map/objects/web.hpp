#pragma once
#include "../../common/images.hpp"
#include "abstract/abstractGameObject.hpp"

class Web : public AbstractGameObject {
public:
    Web(int x, int y, Direction direction) : AbstractGameObject(x, y, ZIndex::WEB) {
        sprite.setTexture(images::web);
        if (direction == Direction::RIGHT) {
            sprite.flipDirection();
        }
    }
};

