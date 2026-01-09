#pragma once
#include "abstractInteractingWithPlayerGameObject.hpp"

class Spike : public AbstractInteractingWithPlayerGameObject {
protected:
    inline static const float PLAYER_Y_VEL_TO_HIT = 5.f;

    void _handleCollisionWithPlayer() override {
        if (player->getYvel() >= PLAYER_Y_VEL_TO_HIT) {
            player->hit();
        }
    }

public:
    Spike(int x, int y, Player* player) : AbstractInteractingWithPlayerGameObject(x, y, player) {
        sprite.setTexture(images::spike);
    }
};
