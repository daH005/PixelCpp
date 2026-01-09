#pragma once
#include "abstractInteractingWithPlayerGameObject.hpp"

class Water : public AbstractInteractingWithPlayerGameObject {
protected:

    void _handleCollisionWithPlayer() override {
        player->setAsInWater();
    }

public:
    Water(int x, int y, Player* player, bool isTop = false) : AbstractInteractingWithPlayerGameObject(x, y, player, ZIndex::OVERLAY) {
        if (isTop) {
            sprite.setTexture(images::topWater);
        }
        else {
            sprite.setTexture(images::water);
        }
    }
};
