#pragma once
#include "../../common/images.hpp"
#include "../../common/zIndex.hpp"
#include "abstract/abstractGameObject.hpp"

class Overlay : public AbstractGameObject {
public:
    Overlay(int x, int y, int w, int h) : AbstractGameObject(x, y, ZIndex::OVERLAY) {
        sprite.setTexture(images::overlay);
        sprite.setScale(w / 40, h / 40);
    }
};
