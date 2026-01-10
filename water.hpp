#pragma once
#include "abstractInteractingWithPlayerGameObject.hpp"

class AbstractWater : public AbstractInteractingWithPlayerGameObject {
protected:
    virtual void _handleCollisionWithPlayer() override {
        player->setAsInWater();
    }

public:
    AbstractWater(int x, int y, Player* player) : AbstractInteractingWithPlayerGameObject(x, y, player, ZIndex::OVERLAY) {}

};

class Water : public AbstractWater {
public:
    Water(int x, int y, Player* player) : AbstractWater(x, y, player) {
        sprite.setTexture(images::water);
    }

};

class TopWater : public AbstractWater {
protected:

    inline static const float TREMBLING_DEVIATION = 3;
    inline static const float TREMBLING_SPEED_UP = -0.1;

    int startTremblingY;
    int endTremblingY;

    void _handleCollisionWithPlayer() override {
        AbstractWater::_handleCollisionWithPlayer();
        sprite.setPosition(sprite.getPosition().x, endTremblingY);
    }

    void updateTrembling() {
        if (sprite.getGlobalBounds().top > startTremblingY) {
            sprite.move(0, TREMBLING_SPEED_UP);

            if (sprite.getGlobalBounds().top < startTremblingY) {
                sprite.setPosition(sprite.getGlobalBounds().left, startTremblingY);
            }
        }
    }

public:
    TopWater(int x, int y, Player* player) : AbstractWater(x, y, player), startTremblingY(y) {
        endTremblingY = startTremblingY + TREMBLING_DEVIATION;
        sprite.setTexture(images::topWater);
    }

    void update() override {
        updateTrembling();
        AbstractInteractingWithPlayerGameObject::update();
    }

};
