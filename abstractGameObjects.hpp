#pragma once
#include "window.hpp"
#include "zIndex.hpp";

class AbstractGameObject {
protected:
    Sprite sprite;
    bool toBeDeleted = false;
    int zIndex;

    void virtual updateTexture() {}

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

class AbstractBlock : public AbstractGameObject {
public:
    AbstractBlock(int x, int y) : AbstractGameObject(x, y, ZIndex::BLOCK) {}

    const FloatRect getRect() const {
        return sprite.getGlobalBounds();
    }
};

class AbstractBackground : public AbstractGameObject {
public:
    AbstractBackground(int x, int y) : AbstractGameObject(x, y, ZIndex::BACKGROUND) {}
};
