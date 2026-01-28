#pragma once
#include "../../common/images.hpp"
#include "../../common/zIndex.hpp"
#include "abstract/abstractGameObject.hpp"

class Tree : public AbstractGameObject {
public:
    Tree(int x, int y, int imageIndex) : AbstractGameObject(x, y, ZIndex::TREE) {
        sprite.setTexture(images::trees[imageIndex]);
    }
};
