#pragma once
#include "abstractEnemy.hpp"

class AbstractXPatrolEnemy : public AbstractEnemy {
protected:
    int startX;
    int endX;

    float xPush;
    float yPush;

    float xvel = speed;

    virtual void handleCollisionWithPlayerAction() override {
        player->hit();
        player->pushY(yPush);
        player->pushX(xPush, sprite.getCenterX());
    }

    virtual void move() {
        if (sprite.getLeft() <= startX) {
            xvel = speed;
            sprite.setDirection(Direction::RIGHT);
        }
        else if (sprite.getRight() >= endX) {
            xvel = -speed;
            sprite.setDirection(Direction::LEFT);
        }
        sprite.moveX(xvel);
    }

public:
    AbstractXPatrolEnemy(int x, int y, Player* player,
        int startX, int endX, float speed,
        float xPush, float yPush
    ) : AbstractEnemy(x, y, player, speed),
        startX(startX), endX(endX),
        xPush(xPush), yPush(yPush) {
    }

    void update() override {
        move();
        AbstractInteractingWithPlayerGameObject::update();
    }

};
