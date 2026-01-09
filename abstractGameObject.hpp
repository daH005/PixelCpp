#pragma once
#include "window.hpp"
#include "zIndex.hpp"

class AbstractGameObject {
protected:
    Sprite sprite;
    bool toBeDeleted = false;
    int zIndex;

    virtual void updateTexture() {}

public:
    AbstractGameObject(int x, int y, int zIndex = 0) : sprite(), zIndex(zIndex) {
        sprite.setPosition(x, y);
    }

    virtual void update() {
        updateTexture();
        window->draw(sprite);
    }

    const Sprite& getSprite() const {
        return sprite;
    }

    bool getToBeDeleted() const {
        return toBeDeleted;
    }

    int getZIndex() const {
        return zIndex;
    }

};
