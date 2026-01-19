#pragma once
#include "window.hpp"
#include "zIndex.hpp"
#include "spriteWrapper.hpp"

class AbstractGameObject {
protected:
    SpriteWrapper sprite;
    bool toBeDeleted = false;
    int zIndex;

    virtual void draw() {
        sprite.draw();
    }

public:
    AbstractGameObject(int x, int y, int zIndex = 0) : sprite(), zIndex(zIndex) {
        sprite.setPosition(x, y);
    }

    virtual void update() {
        draw();
    }

    const SpriteWrapper& getSprite() const {
        return sprite;
    }

    bool getToBeDeleted() const {
        return toBeDeleted;
    }

    int getZIndex() const {
        return zIndex;
    }

};
