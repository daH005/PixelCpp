#pragma once
#include "abstractGameObjects.hpp"
#include "camera.hpp"

class MapBackground : public AbstractGameObject {
protected:
    const float SMOOTH = 0.03f;

    Camera& camera;
    int y;
    int halfW;

public:
    MapBackground(Camera& camera) : AbstractGameObject(0, 0), camera(camera) {
        sprite.setTexture(images::mapBackground);
        y = window->getSize().y - sprite.getGlobalBounds().height;
        halfW = window->getSize().x / 2;
    }

    void reset() {
        sprite.setPosition(0, y);
    }

    void update() override {
        float x = min((-camera.getView().getCenter().x + halfW) * SMOOTH, 0.f);
        sprite.setPosition(x, sprite.getPosition().y);
        AbstractGameObject::update();
    }

};
