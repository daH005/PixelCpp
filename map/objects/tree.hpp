#pragma once
#include "../../common/images.hpp"
#include "abstract/abstractGameObject.hpp"

class Tree : public AbstractBackground {
public:
    Tree(int x, int y, int imageIndex) : AbstractBackground(x, y) {
        sprite.setTexture(images::trees[imageIndex]);
    }
};
