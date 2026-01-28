#pragma once
#include "abstractInteractingWithPlayerGameObject.hpp"

class AbstractEnemy : public AbstractInteractingWithPlayerGameObject {
protected:
    float speed;

    virtual void handleCollisionWithPlayerAction() override {
        player->hit();
    }

public:
    AbstractEnemy(int x, int y, Player* player, float speed, int zIndex = ZIndex::MOVING_OBJECT) : AbstractInteractingWithPlayerGameObject(x, y, player, zIndex), speed(speed) {}
};
