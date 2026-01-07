#pragma once
#include "abstractInteractingWithPlayerGameObject.hpp"

class Ladder : public AbstractInteractingWithPlayerGameObject {
protected:

    void _handleCollisionWithPlayer() override {
        player.setAsOnLadder();
    }

public:
    Ladder(int x, int y, Player& player) : AbstractInteractingWithPlayerGameObject(x, y, player) {
        sprite.setTexture(images::ladder);
    }
};
