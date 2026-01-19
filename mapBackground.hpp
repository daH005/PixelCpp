#pragma once
#include "abstractGameObject.hpp"
#include "camera.hpp"

class MapBackground : public AbstractGameObject {
protected:
    inline static const float SMOOTH = 0.03;

    Camera& camera;
    int y;
    int halfW;

public:
    MapBackground(Camera& camera) : AbstractGameObject(0, 0), camera(camera) {
        sprite.setTexture(images::mapBackground);
        y = window->getSize().y - sprite.getHeight();
        halfW = window->getSize().x / 2;
    }

    void reset() {
        sprite.setPosition(0, y);
    }

    void update() override {
        float x = min((-camera.getView().getCenter().x + halfW) * SMOOTH, 0.f);
        sprite.setLeft(x);
        AbstractGameObject::update();
    }

};
