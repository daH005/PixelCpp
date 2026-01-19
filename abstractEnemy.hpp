#pragma once
#include "abstractInteractingWithPlayerGameObject.hpp"

class AbstractEnemy : public AbstractInteractingWithPlayerGameObject {
protected:
    float speed;

    virtual void handleCollisionWithPlayerAction() override {
        player->hit();
    }

public:
    AbstractEnemy(int x, int y, Player* player, float speed) : AbstractInteractingWithPlayerGameObject(x, y, player, ZIndex::MOVING_OBJECT), speed(speed) {}
};
