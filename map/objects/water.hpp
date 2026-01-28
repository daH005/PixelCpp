#pragma once
#include "abstract/abstractInteractingWithPlayerGameObject.hpp"

class AbstractWater : public AbstractInteractingWithPlayerGameObject {
protected:
    virtual void handleCollisionWithPlayerAction() override {
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

    void handleCollisionWithPlayerAction() override {
        AbstractWater::handleCollisionWithPlayerAction();
        sprite.setTop(endTremblingY);
    }

    void updateTrembling() {
        if (sprite.getTop() > startTremblingY) {
            sprite.moveY(TREMBLING_SPEED_UP);

            if (sprite.getTop() < startTremblingY) {
                sprite.setTop(startTremblingY);
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
        AbstractWater::update();
    }

};
