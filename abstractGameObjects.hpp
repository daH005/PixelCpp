#pragma once
#include "window.hpp"

class AbstractGameObject {
protected:
    Sprite sprite;

    void virtual updateTexture() {}

public:
    AbstractGameObject(int x, int y) : sprite() {
        sprite.setPosition(x, y);
    }

    void update() {
        updateTexture();
        window->draw(sprite);
    }

    Sprite& getSprite() {
        return sprite;
    }

};

class AbstractBlock : public AbstractGameObject {
public:
    AbstractBlock(int x, int y) : AbstractGameObject(x, y) {}
};
